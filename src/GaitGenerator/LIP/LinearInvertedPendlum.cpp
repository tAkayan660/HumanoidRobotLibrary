#include "LinearInvertedPendlum.h"

using namespace cit;

float deg2rad(float degree)
{
	float radian = M_PI * degree / 180.0f;
	return radian; 
}

void LinearInvertedPendlum::SetFootStep()
{
	this->foot_step_list.push_back(Vector3f(0.0, 0.2, 0.0));
	this->foot_step_list.push_back(Vector3f(0.25, 0.2, 20.0));
	this->foot_step_list.push_back(Vector3f(0.25, 0.2, 40.0));
	this->foot_step_list.push_back(Vector3f(0.25, 0.2, 60.0));
	this->foot_step_list.push_back(Vector3f(0.0, 0.2, 60.0));
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
		cog_list_x.push_back(x); cog_list_y.push_back(y);
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
#if 0
	px = p_list_x[count] + cos(deg2rad(foot_step_list[count][2]))*foot_step_list[count][0] - sin(deg2rad(foot_step_list[count][2]))*(-1*pow(-1,count+1)*foot_step_list[count][1]);
	py = p_list_y[count] + sin(deg2rad(foot_step_list[count][2]))*foot_step_list[count][0] + cos(deg2rad(foot_step_list[count][2]))*(-1*pow(-1,count+1)*foot_step_list[count][1]);
#endif
	p_list_x.push_back(px); p_list_y.push_back(py);
}

//STEP 6
void LinearInvertedPendlum::CalcWalkFragment()
{
	xb = foot_step_list[count+1][0]/2;
	yb = pow(-1,count+1)*foot_step_list[count+1][1]/2;
	vxb = ((cosh(t_sup/Tc)+1)/(Tc*sinh(t_sup/Tc)))*xb;
	vyb = ((cosh(t_sup/Tc)-1)/(Tc*sinh(t_sup/Tc)))*yb;
#if 0
	xb = cos(deg2rad(foot_step_list[count+1][2]))*foot_step_list[count+1][0]/2 - sin(deg2rad(foot_step_list[count+1][2]))*pow(-1,count+1)*foot_step_list[count+1][1]/2;
	yb = sin(deg2rad(foot_step_list[count+1][2]))*foot_step_list[count+1][0]/2 + cos(deg2rad(foot_step_list[count+1][2]))*pow(-1,count+1)*foot_step_list[count+1][1]/2;
	vxb = cos(deg2rad(foot_step_list[count+1][2]))*(1+C)/(Tc*S)*xb - sin(deg2rad(foot_step_list[count+1][2]))*(C-1)/(Tc*S)*yb;
	vyb = sin(deg2rad(foot_step_list[count+1][2]))*(1+C)/(Tc*S)*xb + cos(deg2rad(foot_step_list[count+1][2]))*(C-1)/(Tc*S)*yb;
#endif
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
	pxa = -a*(C-1)/D*(xd - C*xi - Tc*S*dxi) - b*S/(Tc*D)*(dxb - S/Tc*xi - C*dxi);
	pya = -a*(C-1)/D*(yd - C*yi - Tc*S*dyi) - b*S/(Tc*D)*(dyb - S/Tc*yi - C*dyi);
	p_modi_list_x.push_back(pxa); p_modi_list_y.push_back(pya);
}

