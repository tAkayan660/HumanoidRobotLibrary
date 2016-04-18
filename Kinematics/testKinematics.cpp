#include "Kinematics.h"

using namespace std;
using namespace MotionControl;

double rad2deg(double radian)
{
	double degree = radian * 180.0f / pi;
	return degree;
}

double deg2rad(double degree)
{
	double radian = degree * pi / 180.0f;
	return radian;
}

int main(int argc, char* argv[])
{
	//Initialize
	Link ulink[LEG_JOINT_NUM];
	SetJointInfo(ulink);
	Kinematics kine(ulink);

	//Set Angle to Joint
	for(int i=0;i<LEG_JOINT_NUM;i++)
		kine.ulink[i].q = 0.0f;
	
	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);	
	cout<<"rarm:"<<kine.ulink[RLEG_JOINT5].p<<endl;	
	return 0;
}
