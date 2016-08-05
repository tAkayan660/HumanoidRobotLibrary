#include "Riccati.h"
#include <Eigen/Core>

using namespace cit;
using namespace Eigen;

int main(int argc, char *argv[])
{
	const float dt = 0.01;
	Matrix<float,3,3> A(Matrix<float,3,3>::Zero());
	Matrix<float,3,1> b(Matrix<float,3,1>::Zero());
	Matrix<float,1,3> c(Matrix<float,1,3>::Zero());
	const float Q = 1e+8;
	const float R = 1.0;

	A << 1, dt, 0.5*dt*dt,
		 0, 1, dt,
		 0, 0, 1;
	b << (dt*dt*dt)/6.0, 0.5*dt*dt, dt;
	c << 1, 0, -0.27/9.81;

	RiccatiEquation<3> riccati(A,b,c,Q,R);
	riccati.calc_riccati_equation();

	cout<<"P:"<<riccati.P<<endl;
	cout<<"K:"<<riccati.K<<endl;

	return 0;
}
