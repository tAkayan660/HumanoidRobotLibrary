#ifndef _FOOTSTEPPLANNER_H_
#define _FOOTSTEPPLANNER_H_

#include <iostream>
#include <deque>
#include <cmath>

#include <Eigen/Core>

using namespace Eigen;

enum leg_type = {RLEG=-1, LLEG=1, BOTH=0};
enum walk_state = {START, WALK, STOP};

class FootStepPlanner{
public:
	FootStepPlanner(double foot_period, double dist_offset);
	void getNextStep(Vector2d tP_B, double tth_B);
	void shiftFootVec();
	void setStopFlag(){walk_state = STOP;}
	Vector2d CoordinatesTransform(Vector2d vec, double th);
	leg_type getSupportLeg(){return this->support_leg;}
	walk_state getWalkState(){return this->status;}

	std::deque<Vector3d> refzmp_list;	// 目標ZMPリスト
	std::deque<Vector2d> tpb_list;		// 目標体幹位置リスト
	std::deque<Vector2d> dpk_list;		// 目標脚配置リスト
private:
	double foot_time, foot_period;
	double dist_offset, swing_step;

	Vector2d tP_K;
	Vector2d P_FB;
	double tth_K, th_FB;
		
	leg_type support_leg;
	walk_state status;
};

#endif
