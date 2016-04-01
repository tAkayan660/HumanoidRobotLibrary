#include "Kinematics.h"

using namespace std;
using namespace MotionControl;

int main(int argc, char* argv[])
{
	Link ulink[LEG_JOINT_NUM];
	SetJointInfo(ulink);
	Kinematics kine(ulink);

	//Set Angle to Joint
	for(int i=0;i<LEG_JOINT_NUM;i++)
		kien.ulink[i].q = 0.0f;
	kine.ulink[HIP_PITCH_L].q = -20 * pi / 180.0f;
	kine.ulink[KNEE_PITCH_L].q = 40 * pi / 180.0f;
	kine.ulink[FOOT_PITCH_L].q _ -20 * pi / 180.0f;

	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);

	//Set Target Position of End Link
	Link target_Lfoot;
	const float move_eef=20.0;
	target_Lfoot.p(0) = kine.ulink[FOOT_ROLL_L].p(0);
	target_Lfoot.p(1)= kine.ulink[FOOT_ROLL_L].p(1);
	target_Lfoot.p(2) = kine.ulink[FOOT_ROLL_L].p(2)+move_eef;

	//Display Target Position
	cout<<"Target Pos"<<endl;
	cout<<target_Lfoot.p<<endl;
	cout<<target_Lfoot.R<<endl;
	cout<<"\n";

	//Calculation Inverse Kinematics
	kine.calcInverseKinematics(FOOT_ROLL_L,target_Lfoot);
	cout<<"calc InverseKinematics..."<<endl;
	cout<<ulink[HIP_PITCH_L].q*180.0f/pi<<endl;
	cout<<ulink[KNEE_PITCH_L].q*180.0f/pi<<endl;
	
	return 0;
}
