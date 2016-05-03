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

	double move_eef_x = 0.0, move_eef_y = 0.0, move_eef_z = 0.0;

	//Initialize
	Link ulink[JOINT_NUM];
	SetJointInfo(ulink);
	Kinematics kine(ulink);


	//Set Angle to Joint
	for(int i=0;i<JOINT_NUM;i++)
		kine.ulink[i].q = 0.0f;
	
	kine.ulink[RLEG_JOINT2].q = deg2rad(-20);
	kine.ulink[RLEG_JOINT3].q = deg2rad(40);
	kine.ulink[RLEG_JOINT4].q = deg2rad(-20);

	while(1){
	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);
	
	cout << "Foward Kinematics calc:";
	cout << kine.ulink[RLEG_JOINT5].p << "\n";
	
	//Calsulation Inverse Kinematics
	Link RLink;
	//RLink.p = kine.ulink[RLEG_JOINT5].p;

	//input effect to posetion

	cout << "input move_x:";
	cin >> move_eef_x;
	cout << "input move_y:";
	cin >> move_eef_y;
	cout << "input move_z:";
	cin >> move_eef_z;

	if(cin.good() == 0) return 0;

		RLink.p(0) = kine.ulink[RLEG_JOINT5].p(0) + move_eef_x; 
		RLink.p(1) = kine.ulink[RLEG_JOINT5].p(1) + move_eef_y;
		RLink.p(2) = kine.ulink[RLEG_JOINT5].p(2) + move_eef_z;

	kine.calcInverseKinematics(RLEG_JOINT5, RLink);

	cout << "Foot Link Pos:";
	cout <<"\n"<< kine.ulink[RLEG_JOINT5].p << "\n";

	for(int i=0; i<7; i++)
		cout<<kine.ulink[i].joint_name<<":"<<rad2deg(kine.ulink[i].q)<<endl;

	}///

	return 0;
}
