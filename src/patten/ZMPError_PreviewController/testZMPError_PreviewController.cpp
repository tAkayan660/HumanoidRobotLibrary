#include "ZMPErrorPreviewController.h"
#include <string>

int main(int argc, char *argv[])
{
	FILE *gp;
	Vector2d com_pos, com_vel, com_acc;
	vector<Vector3d> foot_step_list;
	vector<Vector2d> cog_list, refzmp, outputzmp;

	ZMPErrorPreviewControl expreview_node(0.01, 1.6, 0.27);

	foot_step_list.push_back(Vector3d(0.0,0.0,0.0));
	foot_step_list.push_back(Vector3d(0.32,0.0,0.05));
	foot_step_list.push_back(Vector3d(0.64,0.05,-0.05));
	foot_step_list.push_back(Vector3d(0.96,0.1,0.05));
	foot_step_list.push_back(Vector3d(1.28,0.1,0.0));
	foot_step_list.push_back(Vector3d(3.28,0.20,0.0));
	
	expreview_node.interpolation_zmp_trajectory(foot_step_list);

	gp = popen("gnuplot -persist\n", "w");
//	fprintf(gp, "set xrange [-0.005:0.023]\n");
	//fprintf(gp, "set yrange [-0.06:0.06]\n");
	fprintf(gp, "set xlabel \"x\"\n");
	fprintf(gp, "set ylabel \"y\"\n");

	while(expreview_node.calc_xk(com_pos, com_vel, com_acc)){
		Matrix<double,2,1> temp_refzmp; Matrix<double,1,2> temp_outputzmp;
		expreview_node.get_ref_zmp(temp_refzmp);
		expreview_node.get_current_zmp(temp_outputzmp);
		cog_list.push_back(com_pos);
		refzmp.push_back(temp_refzmp);
		outputzmp.push_back(temp_outputzmp);
	}
	
	fprintf(gp, "plot '-' with lines lw 2, '-' with lines lw 2, '-' with lines lw 2\n");
	for(size_t i=0;i<cog_list.size();i++) fprintf(gp, "%f\t%f\n", cog_list[i](0), cog_list[i](1)); fprintf(gp, "e\n");
	for(size_t i=0;i<refzmp.size();i++) fprintf(gp, "%f\t%f\n", refzmp[i](0), refzmp[i](1)); fprintf(gp, "e\n");
	for(size_t i=0;i<outputzmp.size();i++) fprintf(gp, "%f\t%f\n", outputzmp[i](0), outputzmp[i](1)); fprintf(gp, "e\n");
	fprintf(gp, "exit\n");
	pclose(gp);

	return 0;
}
