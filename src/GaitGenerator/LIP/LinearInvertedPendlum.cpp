#include "LinearInvertedPendlum.h"

using namespace cit;

void LinearInvertedPendlum::SetFootStep()
{
	this->foot_step_list.push_back(Vector3f(0.0, 0.2, 0.0));
	this->foot_step_list.push_back(Vector3f(0.3, 0.2, 0.0));
	this->foot_step_list.push_back(Vector3f(0.3, 0.2, 0.0));
	this->foot_step_list.push_back(Vector3f(0.3, 0.2, 0.0));
	this->foot_step_list.push_back(Vector3f(0.0, 0.2, 0.0));
}

//STEP 3 & 4
void LinearInvertedPendlum::Integrate(int count)
{
	float x, y;
	float dx, dy;

	this->count = count;
	
	//STEP3
	for(float t=0.0;t<t_sup;t+=dt)
	{
		Vector2f temp_cog(0.0, 0.0);
		x = (xi-pxa)*cosh(t/Tc) + Tc*dxi*sinh(t/Tc) + pxa;
		y = (yi-pya)*cosh(t/Tc) + Tc*dyi*sinh(t/Tc) + pya;
		dx = (xi-pxa)/Tc*sinh(t/Tc) + dxi*cosh(t/Tc);
		dy = (yi-pya)/Tc*sinh(t/Tc) + dyi*cosh(t/Tc);
		temp_cog << x, y;
		cog_list.push_back(temp_cog);
	}

	//STEP4
	T =+ t_sup;
	xi = x; yi = y;
	dxi = dx; dyi = dy;
}

//STEP 5
void LinearInvertedPendlum::CalcLegLandingPos()
{
	Vector2f temp_p(0.0, 0.0);
	px = px + foot_step_list[count][0];
	py = py - (pow(-1,count)*foot_step_list[count][1]);
	temp_p << px, py;
	p_list.push_back(temp_p);
}

//STEP 6
void LinearInvertedPendlum::CalcWalkFragment()
{
	xb = foot_step_list[count+1][0]/2;
	yb = pow(-1,count)*foot_step_list[count+1][1]/2;
	vxb = (cosh(t_sup/Tc)+1)/(Tc*sinh(t_sup/Tc))*xb;
	vyb = (cosh(t_sup/Tc)-1)/(Tc*sinh(t_sup/Tc))*yb;
}

//STEP 7
void LinearInvertedPendlum::CalcGoalState()
{
	xd = px + xb;
	dxb = vxb;
	yd = py + yb;
	dyb = vyb;
}

//STEP 8
void LinearInvertedPendlum::ModifyLandPos()
{
	Vector2f temp_p_modi(0.0, 0.0);
	pxa = -a*(cosh(t_sup/Tc)/D)*(xd-cosh(t_sup/Tc)*xi-Tc*sinh(t_sup/Tc)*dxi) - b*(sinh(t_sup/Tc)/(Tc*D))*(dxb-(sinh(t_sup/Tc)/Tc)*xi-cosh(t_sup/Tc)*dxi);
	pya = -a*(cosh(t_sup/Tc)/D)*(yd-cosh(t_sup/Tc)*yi-Tc*sinh(t_sup/Tc)*dyi) - b*(sinh(t_sup/Tc)/(Tc*D))*(dyb-(sinh(t_sup/Tc)/Tc)*yi-cosh(t_sup/Tc)*dyi);
	temp_p_modi << pxa, pya;
	p_modi_list.push_back(temp_p_modi);
}

