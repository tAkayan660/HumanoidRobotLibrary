#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <boost/math/constants/constants.hpp>

using namespace std;
using namespace Eigen;

namespace MotionControl
{
	/* 定数となる物理パラメータ */
	static const float ACCELERATION_OF_GRAVITY = -9.810;
	static const float HEIGHT_ZC = 0.270;
	static const float PI = boost::math::constants::pi<double>();
	static int loop_step = 0;

	/* ZMP予見制御を計算するクラス */
	class ZMPPreviewControl
	{
		protected:
			Matrix<float,3,3> A;	//
			Matrix<float,3,1> b;	//
			Matrix<float,1,3> c;	//

			Matrix<float,3,2> xk;	//計算される重心(位置，速度，加速度)
			Matrix<float,3,2> xkp;	//t-1における重心
			Matrix<float,1,2> u;	//制御入力
			Matrix<float,1,2> p;	//出力ZMP
			Matrix<float,1,2> e;	//ZMP誤差
			float fi;				//フィードバックゲイン

			int gait_count;
			int stop_time;

			const float preview_delay;	//予見制御幅
			const float dt;				//サンプリングタイム
			
			const double Q,R;

		private:
			/* 拡大系のシステム */
			Matrix<float,4,4> phi;
			Matrix<float,4,1> G;
			Matrix<float,4,1> GR;
			Matrix<float,4,4> xi0;
			Matrix<float,4,2> xk_ex;
			Matrix<float,4,4> P;
			Matrix<float,1,4> K;

			Matrix<float,2,1> temp_refzmp;

		public:
			vector<Vector2f> refzmp;
		public:
			/* 定数となるパラメータの初期化 */
			ZMPPreviewControl(const float _dt, const float _preview_delay, const double _Q=1e+08, const double _R=1.0)
				: dt(_dt),
				  preview_delay(_preview_delay),
					stop_time(1.0),
				  xk(Matrix<float,3,2>::Zero()),
				  xkp(Matrix<float,3,2>::Zero()),
					xk_ex(Matrix<float,4,2>::Zero()),
				  u(Matrix<float,1,2>::Zero()),
				  p(Matrix<float,1,2>::Zero()),
				  Q(_Q),
				  R(_R)
			{
				A << 1, dt, 0.5*dt*dt,
					 0, 1, dt,
					 0, 0, 1;
				b << dt*dt*dt/6.0, 0.5*dt*dt, dt;
				c << 1, 0, HEIGHT_ZC / ACCELERATION_OF_GRAVITY;
			}

			/**/
			void ExtendPreviewControlParam()
			{
				Matrix<float,1,3> cA(c*A);
				Matrix<float,1,1> cb(c*b);
				Matrix<float,4,4> I(Matrix<float,4,4>::Identity());

				phi << 1, -cA(0), -cA(1), -cA(2),
					   0, A(0,0), A(0,1), A(0,2),
					   0, A(1,0), A(1,1), A(1,2),
					   0, A(2,0), A(2,1), A(2,2);
				G << -cb, b(0), b(1), b(2);
				GR <<1, 0, 0, 0;
				P << 3.4360e+09, -5.7313e+10, -9.7980e+09, -4.8302e+07,
						-5.7313e+10, 9.8950e+11, 1.6919e+11, 8.3865e+08,
						-9.7980e+09, 1.6919e+11, 2.8929e+10, 1.4345e+08,
						-4.8302e+07, 8.3865e+08, 1.4345e+08, 7.2054e+05;
				K << 2.6772e+03, -9.1990e+04, -1.6264e+04, -172.6188;

				xi0 = (I-G*(1.0/(R+G.transpose()*P*G))*G.transpose()*P)*phi;
			}

			/* 目標ZMPの補間 */
			void RefZmpTrajectory(vector<Vector4f> foot_step_list);

			/* 目標ZMPの取得 */
			void get_ref_zmp(Matrix<float,2,1> &refzmp)
			{
				refzmp = this->temp_refzmp;
			}
			
			/* 出力ZMPの取得 */
			void get_current_zmp(Matrix<float,1,2> &current_zmp)
			{
				current_zmp = p;
			}

			/* 制御入力の計算 */
			void calc_u();

			/* 重心軌道の計算 */
			bool calc_xk(Vector2f &cog);
	};
}

