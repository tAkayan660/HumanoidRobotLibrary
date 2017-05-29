#include "../../planning/FootStepPlanner/FootStepPlanner.h"
#include "../../patten/PreviewController/PreviewControl.h"

#include <iostream>

#include <Eigen/Core>

using namespace std;
using namespace Eigen;

class testGaitGenerator{
public:
	testGaitGenerator(const double _dt, const double _gait_period, const double _zc)
		: dt(_dt), gait_period(_gait_period)
	{
		preview_node = new preview_control(_dt, 1.6, 0.27, _zc);
		plan_node = new FootStepPlanner(_gait_period, 0.04);
	}
	void run(int max_step, const double torso_x, const double torso_y, const double torso_th)
	{
		Vector2d tP_B;
		double tth_B;

		int count = 0;
		while(1){
			plan_node->getNextStep(tP_B, tth_B);
			if(plan_node->getWalkState() == STOP) break;

			count++;
			if(max_step <= count) plan_node->setStopFlag();

			tP_B += Vector2d(torso_x, torso_y); tth_B += torso_th;
		}

		Vector2d com_pos, com_vel, com_acc;
		while(preview_node->update(com_pos, com_vel, com_acc)){
			Vector2d temp_refzmp; RowVector2d temp_outputzmp;
			preview_node->get_ref_zmp(temp_refzmp);
			preview_node->output_zmp(temp_outputzmp);

			com_pos_list.push_back(com_pos);
			refzmp.push_back(temp_refzmp);
			outputzmp.push_back(temp_outputzmp);
		}
	}
	void plot_gait_pattern()
	{
		gp = popen("gnuplot -persist\n", "w");
		fprintf(gp, "set xlabel \"x [m]\"\n");
		fprintf(gp, "set ylabel \"y [m]\"\n");

		fprintf(gp,"plot '-'");
		for(size_t i=0;i<com_pos_list.size();i++) fprintf(gp, "%f\t%f\n", com_pos_list[i](0), com_pos_list[i](1)); fprintf(gp, "e\n");
		for(size_t i=0;i<refzmp.size();i++) fprintf(gp, "%f\t%f\n", refzmp[i](0), refzmp[i](1)); fprintf(gp, "e\n");
		for(size_t i=0;i<outputzmp.size();i++) fprintf(gp, "%f\t%f\n", outputzmp[i](0), outputzmp[i](1)); fprintf(gp, "e\n");
		fprintf(gp, "exit\n");
		pclose(gp);
	}
private:
	FootStepPlanner *plan_node;
	preview_control *preview_node;

	vector<Vector2d> com_pos_list;
	vector<Vector2d> refzmp;
	vector<Vector2d> outputzmp;

	double dt, gait_period;
};

void print_usage()
{
	std::cerr << "Usage: GaitPatternGenerator [test-name]" << std::endl;
	std::cerr << "[test-name]:" << std::endl;
	std::cerr << "--test0 : go pos x." << std::endl;
	std::cerr << "--test1 : go pos y." << std::endl;
	std::cerr << "--test2 : go pos th." << std::endl;
	std::cerr << "--test3 : go pos x y th combination." << std::endl;   
}

int main(int argc, char *argv[])
{
	testGaitGenerator tgg(0.01, 0.32, 0.27);

	if(2 < argc){
		if(string(argv[1]) == "--test0") 
			tgg.run(10, 0.03, 0.0, 0.0);
		else if(string(argv[1]) == "--test1")
			tgg.run(10, 0.0, 0.03, 0.0);
		else if(string(argv[1]) == "--test2")
			tgg.run(10, 0.0, 0.0, 5.0);
		else if(string(argv[1]) == "--test3")
			tgg.run(10, 0.03, 0.03, 5.0);
		else{
			print_usage();
			return -1;
		}
	}else{
		print_usage();
		return -1;
	}

	tgg.plot_gait_pattern();

	return 0;
}
