#include "Kinematics.h"

using namespace std;
using namespace MotionControl;

int main(int argc, char* argv[])
{
	vector<int> idx;
	Link ulink[LEG_JOINT_NUM];
	SetJointInfo(ulink);

	Kinematics kine(ulink);
	
	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);

	//Initial End Link Position
	cout<<"Initial Pos"<<endl;
	cout<<kine.ulink[FOOT_ROLL_L].joint_name<<endl;
	cout<<kine.ulink[FOOT_ROLL_L].p<<endl;
	cout<<"\n";

	//Set Angle to Joint
	ulink[HIP_YAW_L].q = 0.0f;
	ulink[HIP_ROLL_L].q = 0.0f;
	ulink[HIP_PITCH_L].q = -20 * pi / 180.0f;
	ulink[KNEE_PITCH_L].q = 40 * pi / 180.0f;
	ulink[FOOT_PITCH_L].q = -20 * pi / 180.0f;
	ulink[FOOT_ROLL_L].q = 0.0f;
	ulink[HIP_YAW_R].q = 0.0f;
	ulink[HIP_ROLL_R].q = 0.0f;
	ulink[HIP_PITCH_R].q = -20 * pi / 180.0f;
	ulink[KNEE_PITCH_R].q = 40 * pi / 180.0f;
	ulink[FOOT_PITCH_R].q = -20 * pi / 180.0f;
	ulink[FOOT_ROLL_R].q = 0.0f;

	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);

	cout<<"Ready Pos"<<endl;
	cout<<ulink[FOOT_ROLL_L].joint_name<<endl;
	cout<<ulink[FOOT_ROLL_L].p<<endl;
	cout<<"\n";

	//Set Target Position of End Link
	Link target_Lfoot;
	target_Lfoot.p(0) = ulink[FOOT_ROLL_L].p(0);
	target_Lfoot.p(1)= ulink[FOOT_ROLL_L].p(1);
	target_Lfoot.p(2) = ulink[FOOT_ROLL_L].p(2)+20;

	cout<<"Target Pos"<<endl;
	cout<<target_Lfoot.p<<endl;

	//Calculation Inverse Kinematics
	if(kine.calcInverseKinematics(FOOT_ROLL_L,target_Lfoot))
	{
		cout<<"calc InverseKinematics..."<<endl;
		cout<<ulink[HIP_PITCH_L].q<<endl;
		cout<<ulink[KNEE_PITCH_L].q<<endl;
		cout<<ulink[FOOT_PITCH_L].q<<endl;
	}
	return 0;
}