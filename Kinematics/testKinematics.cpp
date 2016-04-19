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
	Link ulink[JOINT_NUM];
	SetJointInfo(ulink);
	Kinematics kine(ulink);

	//Set Angle to Joint
	for(int i=0;i<JOINT_NUM;i++)
		kine.ulink[i].q = 0.0f;
	kine.ulink[RLEG_JOINT2].q = deg2rad(-15.0f);	
	kine.ulink[RLEG_JOINT3].q = deg2rad(40.0f);
	kine.ulink[RLEG_JOINT4].q = deg2rad(-25.0f);
	kine.ulink[LLEG_JOINT2].q = deg2rad(-15.0f);
	kine.ulink[LLEG_JOINT3].q = deg2rad(40.0f);
	kine.ulink[LLEG_JOINT4].q = deg2rad(-25.0f);
	kine.ulink[RARM_JOINT1].q = deg2rad(45.0f);
	kine.ulink[RARM_JOINT2].q = deg2rad(-15.0f);
	kine.ulink[RARM_JOINT4].q = deg2rad(-90.0f);
	kine.ulink[RARM_JOINT5].q = deg2rad(-15.0f);
	kine.ulink[RARM_JOINT7].q = deg2rad(-45.0f);
	kine.ulink[LARM_JOINT1].q = deg2rad(45.0f);
	kine.ulink[LARM_JOINT2].q = deg2rad(15.0f);
	kine.ulink[LARM_JOINT4].q = deg2rad(-90.0f);
	kine.ulink[LARM_JOINT5].q = deg2rad(15.0f);
	kine.ulink[LARM_JOINT7].q = deg2rad(-45.0f);

	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);
	
	cout<<"Right Foot Link pos:"<<endl;
	cout<<kine.ulink[RLEG_JOINT5].p<<endl;
	cout<<"Right Arm Link pos:"<<endl;
	cout<<kine.ulink[RARM_JOINT7].p<<endl;
	
	return 0;
}
