#ifndef _PREVIEWCONTROL_H_
#define _PREVIEWCONTROL_H_

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <boost/math/constants/constants.hpp>

using namespace std;
using namespace Eigen;

/* 定数となる物理パラメータ */
static const double ACCELERATION_OF_GRAVITY = -9.810;
static const double HEIGHT_ZC = 0.270;
static const double PI = boost::math::constants::pi<double>();
static int loop_step = 0;

class ZMPErrorPreviewControl
{
	protected:
		Matrix<double,3,3> A;
		Matrix<double,3,1> b;
		Matrix<double,1,3> c;
		Matrix<double,3,2> xk, xkp;
		Matrix<double,1,2> u;
		Matrix<double,1,2> p, e;
		vector<double> fi;
		int gait_count, stop_time;
		const double dt, preview_delay;
		const double Q,R;
	private:
		Matrix<double,4,4> _A;
		Matrix<double,4,1> _b;
		Matrix<double,1,4> _c;
		Matrix<double,4,2> xk_ex;
		Matrix<double,4,4> xi0;
		Matrix<double,4,4> P;
		Matrix<double,1,4> K;
		Matrix<double,2,1> temp_refzmp;
	public:
		vector<Vector2d> refzmp;
	public:
		/* 定数となるパラメータの初期化 */
		ZMPErrorPreviewControl(const double _dt, const double _preview_delay, const double _Q=1e+06, const double _R=1.0)
			: dt(_dt), preview_delay(_preview_delay), stop_time(1.0),
			  xk(Matrix<double,3,2>::Zero()), xkp(Matrix<double,3,2>::Zero()), xk_ex(Matrix<double,4,2>::Zero()),
			  u(Matrix<double,1,2>::Zero()), p(Matrix<double,1,2>::Zero()), Q(_Q), R(_R)
		{
			A << 1, dt, 0.5*dt*dt,
					 0, 1, dt,
					 0, 0, 1;
			b << dt*dt*dt/6.0, 0.5*dt*dt, dt;
			c << 1, 0, HEIGHT_ZC / ACCELERATION_OF_GRAVITY;

			ExtendPreviewControlParam();
		}
			/* 拡大系 */
		void ExtendPreviewControlParam()
		{
			Matrix<double,1,3> cA(c*A);
			Matrix<double,1,1> cb(c*b);
			Matrix<double,4,4> I(Matrix<double,4,4>::Identity());

			_A << 1, -cA(0), -cA(1), -cA(2),
					   0, A(0,0), A(0,1), A(0,2),
					   0, A(1,0), A(1,1), A(1,2),
					   0, A(2,0), A(2,1), A(2,2);
			_b << -cb, b(0), b(1), b(2);
			_c <<1, 0, 0, 0;
			P << 3.4360e+09, -5.7313e+10, -9.7980e+09, -4.8302e+07,
					-5.7313e+10, 9.8950e+11, 1.6919e+11, 8.3865e+08,
					-9.7980e+09, 1.6919e+11, 2.8929e+10, 1.4345e+08,
					-4.8302e+07, 8.3865e+08, 1.4345e+08, 7.2054e+05;
			K << 2.6772e+03, -9.1990e+04, -1.6264e+04, -172.6188;

			xi0 = (I-_b*(1.0/(R+_b.transpose()*P*_b))*_b.transpose()*P)*_A; 

			calc_f();
		}
		void SetCoMParam(double *com_pos, double *com_vel, double *com_acc)
		{
			xk(0,0) = com_pos[0]; xk(0,1) = com_pos[1];
			xk(1,0) = com_vel[0]; xk(1,1) = com_vel[1];
			xk(2,0) = com_acc[0]; xk(2,1) = com_acc[1];

			xkp = xk;
		}
		void interpolation_zmp_trajectory(vector<Vector3d> foot_step_list);
		void get_ref_zmp(Matrix<double,2,1> &refzmp){ refzmp = this->temp_refzmp; }
		void get_current_zmp(Matrix<double,1,2> &current_zmp){ current_zmp = this->p; }
		void calc_f();
		void calc_u();
		bool calc_xk(Vector2d &com_pos, Vector2d &com_vel, Vector2d &com_acc);
};

#endif
