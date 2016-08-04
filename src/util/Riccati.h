/*
 * @file	Riccati.h
 * @brief	Calculation Riccati Equation for Preview Control.
 * @author	Ryu Yamamoto
 * @date	2016/08/04
 */

#ifndef _RICCATI_H_
#define _RICCATI_H_

#include <iostream>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

namespace cit
{
	template <size_t dim>
	class RiccatiEquation
	{
		private:
			Matrix<float,dim,dim> A;
			Matrix<float,dim,1> b;
			Matrix<float,1,dim> c;
			float Q,R;
		public:
			Matrix<float,dim,dim> P;
			Matrix<float,1,dim> K;
		public:
			RiccatiEquation(const Matrix<float,dim,dim> _A, const Matrix<float,dim,1> _b, const Matrix<float,1,dim> _c, const float _Q, const float _R)
				: A(_A), b(_b), c(_c), Q(_Q), R(_R), P(Matrix<float,dim,dim>::Zero()), K(Matrix<float,1,dim>::Zero())
			{};
			RiccatiEquation(const RiccatiEquation& _RE);	
			bool calc_riccati_equation()	//Numerical Solution
			{
				Matrix<float,dim,dim> P_pre(Matrix<float,dim,dim>::Zero());
				for(int i=0;i<10000;i++)
				{
					K = (1.0/(R+b.transpose()*P*b))*b.transpose()*P;
					P_pre = A.transpose()*P*A+c.transpose()*Q*c-A.transpose()*P*b*K;
					if((abs((P-P_pre).array()) < 1e-10).all())
					{
						K = (1.0/(R+b.transpose()*P*b))*b.transpose()*P;
						return false;
					}
					P = P_pre;
				}
			}
	};
}

#endif
