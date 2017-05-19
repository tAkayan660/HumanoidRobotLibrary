#include "LinearInvertedPendlum.h"

using namespace cit;

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
	
	/* Plot Gait Pattern */
	LIP.plot_gait_pattern_list();
	
	return 0;
}
