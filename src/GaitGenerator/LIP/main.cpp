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
		//cout<<"px:"<<LIP.p_list_x[n]<<" py:"<<LIP.p_list_y[n]<<" pxa:"<<LIP.p_modi_list_x[n]<<" pya:"<<LIP.p_modi_list_y[n]<<endl;
	}

	plt::plot(LIP.cog_list_x, LIP.cog_list_y, "b");
	plt::plot(LIP.p_list_x, LIP.p_list_y, ".g");
	plt::plot(LIP.p_modi_list_x, LIP.p_modi_list_y, "+r");

	plt::show();

	/* Write Center of Mass to Csv File */
	/*fp = fopen("InvetedPendlumCOG.csv", "w");
	for(size_t i=0;i<LIP.cog_list.size();i++)
		fprintf(fp,"%lf %lf\n",LIP.cog_list[i][0],LIP.cog_list[i][1]);
	fclose(fp);*/

	return 0;
}
