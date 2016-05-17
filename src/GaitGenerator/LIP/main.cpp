#include "LinearInvertedPendlum.h"
#include "matplotlibcpp.h"

using namespace cit;
namespace plt = matplotlibcpp;

int main(int argc, char* argv[])
{
	FILE *fp;
	LinearInvertedPendlum LIP(0.8, 0.02, 10, 1);	//STEP 1
	LIP.SetFootStep();	//STEP 2
	LIP.p_list_x.push_back(0.0);
	LIP.p_list_y.push_back(0.0);

	/* Main Loop */
	for(int n=0;n<6;n++)
	{
		LIP.Integrate(n);			//STEP 3 & 4
		LIP.CalcLegLandingPos();	//STEP 5
		LIP.CalcWalkFragment();		//STEP 6
		LIP.CalcGoalState();		//STEP 7
		LIP.ModifyLandPos();		//STEP 8
	}

	plt::title("Gait Pattern by Linear Inverted Pendlum");
	plt::xlabel("x[m]");
	plt::ylabel("y[m]");
	
	plt::named_plot("Center of Mass", LIP.cog_list_x, LIP.cog_list_y, "b");
	plt::named_plot("Foot Landing Pos", LIP.p_list_x, LIP.p_list_y, ".g");
	plt::named_plot("Foot Landing Fixed Pos", LIP.p_modi_list_x, LIP.p_modi_list_y, "+r");
	plt::legend();

	plt::show();

	return 0;
}
