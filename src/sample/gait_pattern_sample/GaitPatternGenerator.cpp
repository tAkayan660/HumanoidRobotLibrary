#include "../../planning/PlanZMPList/ZMPPlanner.h"
#include "../../patten/PreviewController/PreviewControl.h"

#include <iostream>

#include <Eigen/Core>

using namespace std;
using namespace Eigen;

const int ONE_STEP_THRE = 2;
const int MAX_STEP = 1;

class testGaitGenerator{
public:
	testGaitGenerator(const double dt, const double gait_period, const double zc)
		: dt(dt), gait_period(gait_period)
	{
		preview_node = new preview_control(dt, 1.6, zc);
		plan_node = new ZMPPlanner(gait_period, 0.04f);
	}
	void run(int max_step, const double torso_x, const double torso_y, const double torso_th)
	{
		Vector2d tP_B(Vector2d::Zero());
		double tth_B=0.0f;
		int count = 1;
		bool result = true;

		Vector2d prev_refzmp(Vector2d(0.0f,0.0f));
		Vector2d next_refzmp = prev_refzmp;
		while(1){
			// Generate Reference ZMP
			plan_node->refzmp_list.push_back(Vector3d(0.0f,prev_refzmp[0], prev_refzmp[1]));
			tP_B = next_refzmp;
			int temp_count = 0;
			while(1){
				plan_node->getNextZMP(tP_B, tth_B); //temp_count++;
				if(plan_node->getWalkState() == STOP) break;
				temp_count++;
				if(ONE_STEP_THRE <= temp_count) plan_node->setStopFlag();
				tP_B += Vector2d(torso_x, torso_y); tth_B += torso_th;
			}

			// Preview Controller
			preview_node->interpolation_zmp_trajectory(plan_node->refzmp_list);
			double timer = 0;
			Vector2d com_pos, com_vel, com_acc;
			while(preview_node->update(com_pos, com_vel, com_acc)){
				Vector2d temp_refzmp; RowVector2d temp_outputzmp;
				preview_node->get_ref_zmp(temp_refzmp);
				preview_node->output_zmp(temp_outputzmp);

				com_pos_list.push_back(com_pos);
				refzmp.push_back(temp_refzmp);
				outputzmp.push_back(temp_outputzmp.transpose());

				timer += 0.01;
				if(count < max_step){
					if(gait_period <= timer) break;
				}
			}

			prev_refzmp[0] = plan_node->refzmp_list[1][1] + (torso_x/2.0f);
			prev_refzmp[1] = 0.0;//plan_node->refzmp_list[1][1] + (torso_y/2.0f);
			next_refzmp[0] = plan_node->refzmp_list[2][1];
			next_refzmp[1] = 0.0;
			plan_node->clear_buf();
			preview_node->buffer_clear();

			count++;
			if(max_step < count) break;
		}
	}
	void plot_gait_pattern()
	{
		FILE *gp = popen("gnuplot -persist\n", "w");
		fprintf(gp, "set xlabel \"x [m]\"\n");
		fprintf(gp, "set ylabel \"y [m]\"\n");

		fprintf(gp, "plot '-' with lines lw 2 title \"Center of Mass\", '-' with lines lw 2 title \"Reference ZMP\", '-' with lines lw 2 title \"Out Put ZMP\"\n");
		for(size_t i=0;i<com_pos_list.size();i++) fprintf(gp, "%f\t%f\n", com_pos_list[i](0), com_pos_list[i](1)); fprintf(gp, "e\n");
		for(size_t i=0;i<refzmp.size();i++) fprintf(gp, "%f\t%f\n", refzmp[i](0), refzmp[i](1)); fprintf(gp, "e\n");
		//for(size_t i=0;i<outputzmp.size();i++) fprintf(gp, "%f\t%f\n", outputzmp[i](0), outputzmp[i](1)); fprintf(gp, "e\n");
		fprintf(gp, "exit\n");
		pclose(gp);
	}
private:
	ZMPPlanner *plan_node;
	preview_control *preview_node;

	vector<Vector2d> com_pos_list;
	vector<Vector2d> refzmp;
	vector<Vector2d> outputzmp;

	double dt, gait_period;
};

void print_usage()
{
	std::cerr << "Usage: testGaitPatternGenerator [param] <step> <torso x> <torso y> <torso th>" << std::endl;
	std::cerr << "[param]:" << std::endl;
	std::cerr << "	step: max number of foot steps." << std::endl;
	std::cerr << "	torso x: max torso x." << std::endl;
	std::cerr << "	torso y: max torso y."	<< std::endl;
	std::cerr << "	torso th:	max torso th." << std::endl;
}

int main(int argc, char *argv[])
{
	testGaitGenerator tgg(0.01, 0.32, 0.27);

	if(argc == 5){
		int max_step = atoi(argv[1]);
		double torso_x	= static_cast<double>(atof(argv[2]));
		double torso_y	= static_cast<double>(atof(argv[3]));
		double torso_th	= static_cast<double>(atof(argv[4]));

		tgg.run(max_step, torso_x, torso_y, torso_th);
	}else{
		print_usage();
		return -1;
	}

	tgg.plot_gait_pattern();

	return 0;
}
