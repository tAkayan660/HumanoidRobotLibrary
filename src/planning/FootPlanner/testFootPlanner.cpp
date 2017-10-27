#include "FootPlanner.h"

int main(int argc, char *argv[])
{
	FootPlanner plan_node(0.01, 0.32);
	plan_node.SetFootStepParameter(0.06,0.06,0.0,0.05,0.32);
	plan_node.foot_step_list_clear();

	plan_node.SetTargetPos(atof(argv[1]), atof(argv[2]), 0.0, RightLeg, Start);

	FILE *gp = popen("gnuplot -persist\n", "w");
	fprintf(gp, "set xlabel \"x [m]\"\n");
	fprintf(gp, "set ylabel \"y [m]\"\n");
	fprintf(gp, "plot '-' with lines lw 2, '-' with lines lw 2, '-' with lines lw 2\n");
	for(size_t i=0;i<plan_node.foot_step_list.size();i++)
		fprintf(gp,"%f\t%f\n",plan_node.foot_step_list[i](1),plan_node.foot_step_list[i](2));
	fprintf(gp,"e\n");
	fprintf(gp,"exit\n");
	pclose(gp);
	
	return 0;
}
