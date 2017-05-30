#include "Kinematics.h"

#include <iostream>

#include <Eigen/Core>

using namespace std;

int main(int argc, char *argv[])
{
	Link ulink[JOINT_NUM];
	Kinematics ik_node(ulink);
	SetJointInfo(ulink);

	for(int i=0;i<JOINT_NUM;i++)
		ulink[i].q = 0.0f;

	ik_node.calcForwardKinematics(WAIST);

	Matrix<double,3,1> com = calcCoM(ulink);

	cout << com << endl;
}
