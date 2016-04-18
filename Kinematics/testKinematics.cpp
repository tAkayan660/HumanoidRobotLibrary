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
	Link ulink[ARM_JOINT_NUM];
	SetJointInfo(ulink);
	Kinematics kine(ulink);

	//Set Angle to Joint
	for(int i=0;i<ARM_JOINT_NUM;i++)
		kine.ulink[i].q = 0.0f;
	/*kine.ulink[RARM_JOINT1].q = deg2rad(40.0);
	kine.ulink[RARM_JOINT2].q = deg2rad(-15.0);*/
	kine.ulink[RARM_JOINT4].q = deg2rad(-80.0);
	kine.ulink[RARM_JOINT6].q = deg2rad(-80.0);
	/*kine.ulink[RARM_JOINT7].q = deg2rad(-40.0);
	kine.ulink[LARM_JOINT1].q = deg2rad(40.0);
	kine.ulink[LARM_JOINT2].q = deg2rad(15.0);
	kine.ulink[LARM_JOINT3].q = deg2rad(-90.0);
	kine.ulink[LARM_JOINT4].q = deg2rad(15.0);
	kine.ulink[LARM_JOINT7].q = deg2rad(-40.0);*/
	
	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);	
	for(int i=0;i<ARM_JOINT_NUM;i++)
		cout<<kine.ulink[i].joint_name<<": "<<rad2deg(kine.ulink[i].q)<<endl;
	cout<<"larm:"<<kine.ulink[LARM_JOINT7].p<<endl;
	cout<<"rarm:"<<kine.ulink[RARM_JOINT7].p<<endl;
	return 0;
}
