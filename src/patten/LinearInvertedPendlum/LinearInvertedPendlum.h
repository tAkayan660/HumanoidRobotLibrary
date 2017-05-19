#include <iostream>
#include <vector>
#include <math.h>
#include <Eigen/Dense>
#include <boost/math/constants/constants.hpp>

using namespace std;
using namespace Eigen;

namespace cit
{
	static const float Zc = 0.8;
	static const float ACCELALETION_GRAVITY = 9.81;
	
	class LinearInvertedPendlum
	{
		private:
			float t_sup;
			float dt;
			float Tc;
			float C,S,D;
			int count;
			const int a,b;
			float x,y;
			float xi,yi;
			float xb,yb;
			float xd,yd;
			float dx,dy;
			float dxi,dyi;
			float dxb,dyb;
			float vxb,vyb;
			float px,py;
			float pxa,pya;
		public:
			float T;
			vector<Vector3f> foot_step_list;
			vector<float> cog_list_x;
			vector<float> cog_list_y;
			vector<float> p_list_x;
			vector<float> p_list_y;
			vector<float> p_modi_list_x;
			vector<float> p_modi_list_y;
		public:
			LinearInvertedPendlum(float _t_sup, float _dt, int _a, int _b)
				: t_sup(_t_sup),
				  dt(_dt),
				  a(_a),
				  b(_b)
			{
				Tc = sqrt(Zc/ACCELALETION_GRAVITY);
				D = a*pow((cosh(t_sup/Tc)-1),2) + b*pow((sinh(t_sup/Tc)/Tc),2);
				S = sinh(0.8/Tc);
				C = cosh(0.8/Tc);
				
				T = 0;

				//STEP 1
				x = 0.0; y = 0.01;
				dx = 0; dy = 0;
				xi = x; yi = y;
				dxi = dx, dyi = dy;
				px = 0.0; py = 0.0;
				pxa = px; pya = py;
			}
			void SetFootStep();
			void Integrate(int count);
			void CalcLegLandingPos();
			void CalcWalkFragment();
			void CalcGoalState();
			void ModifyLandPos();
			void plot_gait_pattern_list();
	};
}
