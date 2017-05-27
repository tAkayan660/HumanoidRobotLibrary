#include "FootStepPlanner.h"

FootStepPlanner::FootStepPlanner(double _foot_period, double _dist_offset)
	: foot_period(_foot_period),
		foot_time(0.0),
		dist_offset(_dist_offset),
		support_leg(RLEG),
		status(START),
		tP_K(Vector2d::Zero())
{
}

void FootStepPlanner::getNextStep(Vector2d tP_B, double tth_B)
{
	if(tP_B[0] < 0) swing_step = -1*swing_step;

	dP_K = tP_B + CoordinatesTransform(PFB, tth_B);
	dth_K = tth_B + th_FB;

	tpb_list.push_back(tP_B);
	dpk_list.push_back(dP_K);

	refzmp_list.push_back(Vector3d, dP_K[0], dP_K[1]);
	time += foot_period;
}

void FootStepPlanner::shiftFootVec()
{
	if(status == START){
		if(support_leg == RLEG) PFB << 0.0, -dist_offset;
		else if(support_leg == LLEG) PFB << 0.0, dist_offset;
	}else if(status == WALK){
		if(support_leg == RLEG) PFB << swing_step, -dist_offset;
		else if(support_leg == LLEG) PFB << swing_step, dist_offset;
	}else if(status == STOP){
		if(support_leg == RLEG) PFB << 0.0, -dist_offset;
		else if(support_leg) PFB << 0.0, dist_offset;
	}

	if(support_leg == RLEG) support_leg = LLEG;
	else if(support_leg == LLEG) support_leg = RLEG;
}

Vector2d CoordinatesTransform(Vector2d vec, double th)
{
	Vector2d trans_vec(Vector2d::Zero());

	trans_vec[0] = vec[0] * cos(deg2rad(th)) - vec[1] * sin(deg2rad(th));
	trans_vec[1] = vec[1] * sin(deg2rad(th)) + vec[1] * sin(deg2rad(th));

	return trans_vec;
}

