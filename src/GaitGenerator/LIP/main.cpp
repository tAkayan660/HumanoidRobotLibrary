#include "LinearInvertedPendlum.h"

using namespace cit;

int main(int argc, char* argv[])
{
	FILE *fp;
	LinearInvertedPendlum LIP(0.8, 0.02, 10, 1);	//STEP 1
	LIP.SetFootStep();	//STEP 2
	LIP.p_list.push_back(Vector2f(0.0, 0.0));

	/* Main Loop */
	for(int n=0;n<6;n++)
	{
		LIP.Integrate(n);			//STEP 3 & 4
		LIP.CalcLegLandingPos();	//STEP 5
		LIP.CalcWalkFragment();		//STEP 6
		LIP.CalcGoalState();		//STEP 7
		LIP.ModifyLandPos();		//STEP 8
		cout<<"px:"<<LIP.p_list[n][0]<<" py:"<<LIP.p_list[n][1]<<" pxa:"<<LIP.p_modi_list[n][0]<<" pya:"<<LIP.p_modi_list[n][1]<<endl;
	}

	/* Write Center of Mass to Csv File */
	fp = fopen("InvetedPendlumCOG.csv", "w");
	for(size_t i=0;i<LIP.cog_list.size();i++)
		fprintf(fp,"%lf %lf\n",LIP.cog_list[i][0],LIP.cog_list[i][1]);
	fclose(fp);

	return 0;
}
