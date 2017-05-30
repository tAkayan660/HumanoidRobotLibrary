#ifndef _JACOBIAN_H_
#define _JACOBIAN_H_

#include <iostream>
#include <Eigen/Core>

#include "Link.h"

using namespace Eigen;

// 全リンクがあワールド座標系の原点回りに作り出すモーメント
Matrix<double,3,1> calcMC(Link *ulink, int rootlink)
{
	Matrix<double,3,1> mc;

	if(rootlink == -1){
		mc = Matrix<double,3,1>::Zero();
	}else{
		mc = ulink[rootlink].m * (ulink[rootlink].p + ulink[rootlink].R * ulink[rootlink].c);
		mc = mc + calcMC(ulink, ulink[rootlink].sister) + calcMC(ulink, ulink[rootlink].child);
	}

	return mc;
}

MatrixXd calcJacobian(Link *ulink, std::vector<int> idx)
{
	std::size_t jsize = idx.size();
	Matrix<double,3,1> target = ulink[idx.back()].p;
	MatrixXd J;

	J.resize(6,jsize);

	for(std::size_t i=0;i<jsize;i++)
	{
		int j = idx[i];
		Matrix<double,3,1> a = ulink[j].R * ulink[j].a;
		Matrix<double,3,1> b = a.cross(target - ulink[j].p);
		J(0,i) = b(0); J(1,i) = b(1); J(2,i) = b(2);
		J(3,i) = a(0); J(4,i) = a(1); J(5,i) = a(2);
	}

	return J;
}

#endif
