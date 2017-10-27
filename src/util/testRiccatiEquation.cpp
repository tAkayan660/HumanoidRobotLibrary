#include "Riccati.h"
#include <Eigen/Core>

using namespace cit;
using namespace Eigen;

int main(int argc, char *argv[])
{
	Matrix<float,4,4> A(Matrix<float,4,4>::Zero());
	Matrix<float,4,1> b(Matrix<float,4,1>::Zero());
	Matrix<float,1,4> c(Matrix<float,1,4>::Zero());
	const float Q = 1e+8;
	const float R = 1.0;

	A << 1, -1, -0.01, 0.0274729,
		 0, 1, 0.01, 5e-05,
		 0, 0, 1, 0.01,
		 0, 0, 0, 1;
	b << 0.000275063, 1.66667e-07, 5e-05, 0.01;
	c << 1, 0, 0, 0;

	RiccatiEquation<4> riccati(A,b,c,Q,R);
	riccati.calc_riccati_equation();

	cout<<"P:"<<riccati.P<<endl;
	cout<<"K:"<<riccati.K<<endl;

	return 0;
}
