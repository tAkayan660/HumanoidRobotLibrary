#ifndef _PREVIEWCONTROLLER_H_
#define _PREVIEWCONTROLLER_H_

#include <stdio.h>
#include <iostream>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>

using namespace std;
using namespace Eigen;

const double ACCELERATION_OF_GRAVITY = -9.810;

class preview_control
{
	protected:
		Matrix<double,3,3> A;
		Matrix<double,3,1> b;
		Matrix<double,1,3> c;
		Matrix<double,3,2> xk, xkp;
		Matrix<double,1,2> u, up, p;
		Matrix<double,2,1> temp_refzmp;
		vector<double> fi;
		const double dt, preview_delay, zc, stop_time;
		const double Q,R;
		int preview_num, foot_step_num;
	private:
		Matrix<double,3,3> P;
		Matrix<double,1,3> K;
	private:
		void calc_f();
		void calc_u();
		void calc_xk(Vector2d &com_pos, Vector2d &com_vel, Vector2d &com_acc);
		bool update_xk(Vector2d &com_pos, Vector2d &com_vel, Vector2d &com_acc);
	public:
		vector<Vector2d> refzmp;
	public:
		preview_control(const double _dt, const double _preview_delay, const double _zc, const double _Q=1e+08, const double _R=1.0)
			: dt(_dt), preview_delay(_preview_delay), zc(_zc), Q(_Q), R(_R), preview_num(0), stop_time(1.0),
			  xk(Matrix<double,3,2>::Zero()), xkp(Matrix<double,3,2>::Zero()), up(Matrix<double,1,2>::Zero())
		{
			A << 1, dt, (dt*dt)/2,
				 0, 1, dt,
				 0, 0, 1;
			b << (dt*dt*dt)/6.0, (dt*dt)/2, dt;
			c << 1, 0, zc / ACCELERATION_OF_GRAVITY;

		//	calc_riccati_equation<3>(A, b, c, P, K);
			
			calc_f(); 
		}
		~preview_control()
		{}
		template <size_t dim>
		bool calc_riccati_equation(Matrix<double,dim,dim> A, Matrix<double,dim,1> b, Matrix<double,1,dim> c, Matrix<double,dim,dim> &P, Matrix<double,1,dim> &K)
		{
			Matrix<double,dim,dim> P_pre(Matrix<double,dim,dim>::Zero());
			const int MAX_ITERATION = 10000;

			for(int i=0;i<MAX_ITERATION;i++){
				cout << i << endl;
				K = (1.0/(R+b.transpose()*P*b))*b.transpose()*P*A;
				P_pre = A.transpose()*P*A+c.transpose()*Q*c-A.transpose()*P*b*K;
				if((abs((P-P_pre).array()) < 1e-10).all()){
					P = P_pre;
					K = (1.0/(R+b.transpose()*P*b))*b.transpose()*P*A;
					cout << "success" << endl;
					return true;
				}
				P = P_pre;
			}
			std::cerr << "faild." << std::endl;
			return false;
		}
		//void calc_xk(Vector2d &com_pos, Vector2d &com_vel, Vector2d &com_acc);
		void interpolation_zmp_trajectory(vector<Vector3d> foot_step_list);
		void set_com_param(Vector2f &com_pos, Vector2f &com_vel, Vector2f &com_acc);
		void get_ref_zmp(Matrix<double,2,1> &refzmp){refzmp = this->temp_refzmp;}
		void output_zmp(Matrix<double,1,2> &output_zmp){output_zmp = this->p;}
};

class extend_preview_control : public preview_control
{
	private:
		Matrix<double,4,4> _A;
		Matrix<double,4,1> _b;
		Matrix<double,1,4> _c;
		Matrix<double,4,2> _xk;
		Matrix<double,4,4> _P;
		Matrix<double,1,4> _K;
		Matrix<double,1,3> _Kx;
		double _Ks;
		double gj;
	public:
		void calc_f();
		void calc_u();
		void calc_xk(Vector2d &com_pos, Vector2d &com_vel, Vector2d &com_acc);
		bool update_xk(Vector2d &com_pos, Vector2d &com_vel, Vector2d &com_acc);
	public:
		extend_preview_control(const double _dt, const double _preview_delay, const double _zc)
			: _A(Matrix<double,4,4>::Zero()), _b(Matrix<double,4,1>::Zero()), _c(Matrix<double,1,4>::Zero()),
				_xk(Matrix<double,4,2>::Zero()), preview_control(_dt,_preview_delay, _zc), gj(0)
		{
			Matrix<double,1,3> cA;

			_A << 1, cA(0), cA(1), cA(2),
						0, A(0,0), A(0,1), A(0,2),
						0, A(1,0), A(1,1), A(1,2),
						0, A(2,0), A(2,1), A(2,2);
			_b << c*b, b(0), b(1), b(2);
			_c << 1, 0, 0, 0;

		//	calc_riccati_equation<4>(_A, _b, _c, _P, _K);

			_P <<3437692525.62383,	57369803240.9293,	9812475637.03733,	48373761.7798753,
			57369803240.9293,	990949874277.957,	169519465566.811,	840278939.200152,
			9812475637.03733,	169519465566.811,	28999617839.3531,	143799650.968417,
			48373761.7798753,	840278939.200152,	143799650.968417,	722258.932258196;
			_K << -2675.46982037481,	-91974.4260406319,	-16268.8619776505,	-172.653264027794;

			_Ks = _K(0);
			_Kx << _K(1), _K(2), _K(3);
			calc_f();
		}
};

#endif
