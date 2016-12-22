#ifndef _PREVIEWCONTROLLER_H_
#define _PREVIEWCONTROLLER_H_

#include <iostreams>
#include <vector>
#include <deque>

#include <Eigen/Core>

using namespace std;
using namespace Eigen;

static const double ACCELERATION_OF_GRAVITY = -9.810;

class PreviewControl
{
	public:
		PreviewControl(const double _dt, const double _preview_delay, const double _zc, const double _Q=1e-06, const double _R=1.0)
			: dt(_dt), preview_delay(_preview_delay), zc(_zc), R(_R), Q(Matrix<double,3,3>::Zero())
		{
			A << 1, dt, 0.5*dt*dt,
				 0, 1, dt,
				 0, 0, 1;
			b << dt*dt*dt/6.0, 0.5*dt*dt, dt;
			c << 1, 0 , zc / ACCELERATION_OF_GRAVITY;

			Q(0,0) = _Q;

			P << ;
			K << ;
		}
		~PreviewControl();
		void calc_u();
		void calc_f();
		void calc_xk(Vector2d &com_pos, Vector2d &com_vel, Vector2d &com_acc);
		void get_ref_zmp(Vector2d &refzmp){refzmp = this->temp_refzmp;}
		void get_current_zmp(RowVector2d &current_zmp){current_zmp = this->p;}
	protected:
		const double zc;
		const double dt;
		const double preview_delay;
		const double R;
		const Matrix<double,3,3> Q;
		Matrix<double,3,3> A;
		Matrix<double,3,1> b;
		Matrix<double,1,3> c;
		Matrix<double,3,2> xk, xkp;
		Matrix<double,1,2> u, p, e;
		Vector2d temp_refzmp;
	public:
		deque<Vector2d> refzmp;
	private:
		Matrix<double,3,3> P;
		Matrix<double,1,3> K;
};

#endif
