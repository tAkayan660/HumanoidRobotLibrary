#include "Kinematics.h"
#include "../util/func.h"

using namespace std;

int main(int argc, char* argv[])
{
	//Initialize
	Link ulink[JOINT_NUM];
	Kinematics kine(ulink);	
	SetJointInfo(ulink);

	//Set Angle to Joint
	for(int i=0;i<JOINT_NUM;i++)
		ulink[i].q = 0.0;
	cout << RARM_JOINT0 << endl;

	ulink[RARM_JOINT0].q = 0.0;
	ulink[RARM_JOINT1].q = deg2rad(40);
	ulink[RARM_JOINT2].q = deg2rad(-15);
	ulink[RARM_JOINT3].q = 0.0;
	ulink[RARM_JOINT4].q = deg2rad(-90);
	ulink[RARM_JOINT5].q = deg2rad(-15);
	ulink[RARM_JOINT6].q = 0.0;
	ulink[RARM_JOINT7].q = deg2rad(-40);

	//Calculation Forward Kinematics
	kine.calcForwardKinematics(WAIST);
	Link RARM_LINK = ulink[RARM_JOINT7];
	
	for(int i=0;i<1000;i++){
		RARM_LINK.p(2) -= 0.1;
		//Calculation Inverse Kinematics
		cout << "iteration:" << i << endl;
		if(kine.calcInverseKinematics(RARM_JOINT7, RARM_LINK)){
			for(int i=13;i<=25;i++)
				cout << ulink[i].joint_name << ":" << rad2deg(ulink[i].q) << endl;
		}else{
			cout << "Calculation Inverse Kinematics Faild." << endl;
		}
		cout << "\n";
	}
	return 0;
}
