#include "LinearInvertedPendlum.h"

using namespace cit;

void LinearInvertedPendlum::SetFootStep()
{
	this->foot_step_list.push_back(Vector3f(0.0, 0.2, 0.0));
	this->foot_step_list.push_back(Vector3f(0.3, 0.3, 0.0));
	this->foot_step_list.push_back(Vector3f(0.3, 0.1, 0.0));
	this->foot_step_list.push_back(Vector3f(0.3, 0.3, 0.0));
	this->foot_step_list.push_back(Vector3f(0.0, 0.2, 0.0));
	this->foot_step_list.push_back(Vector3f(0.0, 0.0, 0.0));
	this->foot_step_list.push_back(Vector3f(0.0, 0.0, 0.0));
}

//STEP 3 & 4
void LinearInvertedPendlum::Integrate(int count)
{
	float x, y;
	float dx, dy;

	this->count = count;
	
	//STEP3
	for(float t=0.0;t<=t_sup;t+=dt)
	{
		x = (xi-pxa)*cosh(t/Tc) + Tc*dxi*sinh(t/Tc) + pxa;
		y = (yi-pya)*cosh(t/Tc) + Tc*dyi*sinh(t/Tc) + pya;
		dx = (xi-pxa)/Tc*sinh(t/Tc) + dxi*cosh(t/Tc);
		dy = (yi-pya)/Tc*sinh(t/Tc) + dyi*cosh(t/Tc);
		cog_list.push_back(Vector2f(x, y));
	}

	//STEP4
	T =+ t_sup;
	xi = x; yi = y;
	dxi = dx; dyi = dy;
}

//STEP 5
void LinearInvertedPendlum::CalcLegLandingPos()
{
	px = px + foot_step_list[count][0];
	py = py - (pow(-1,count+1)*foot_step_list[count][1]);
	p_list.push_back(Vector2f(px, py));
}

//STEP 6
void LinearInvertedPendlum::CalcWalkFragment()
{
	xb = foot_step_list[count+1][0]/2;
	yb = pow(-1,count+1)*foot_step_list[count+1][1]/2;
	vxb = ((cosh(t_sup/Tc)+1)/(Tc*sinh(t_sup/Tc)))*xb;
	vyb = ((cosh(t_sup/Tc)-1)/(Tc*sinh(t_sup/Tc)))*yb;
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
	pxa = -a*(cosh(t_sup/Tc)-1)/D*(xd - cosh(t_sup/Tc)*xi - Tc*sinh(t_sup/Tc)*dxi) - b*sinh(t_sup/Tc)/(Tc*D)*(dxb - sinh(t_sup/Tc)/Tc*xi - cosh(t_sup/Tc)*dxi);
	pya = -a*(cosh(t_sup/Tc)-1)/D*(yd - cosh(t_sup/Tc)*yi - Tc*sinh(t_sup/Tc)*dyi) - b*sinh(t_sup/Tc)/(Tc*D)*(dyb - sinh(t_sup/Tc)/Tc*yi - cosh(t_sup/Tc)*dyi);
	p_modi_list.push_back(Vector2f(pxa, pya));
}

