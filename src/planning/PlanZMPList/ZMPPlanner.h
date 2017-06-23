#ifndef _ZMPPLANNER_H_
#define _ZMPPLANNER_H_

#include <iostream>
#include <vector>
#include <cmath>

#include <Eigen/Core>

using namespace Eigen;

enum leg_type {RLEG=-1, LLEG=1, BOTH=0};
enum walk_state {START, WALK, STOP};

class ZMPPlanner{
public:
	ZMPPlanner(double foot_period, double dist_offset);
	void getNextZMP(Vector2d tP_B, double tth_B);
	void shiftFootVec();
	void setStopFlag(){status = STOP;}
	Vector2d CoordinatesTransform(Vector2d vec, double th);
	leg_type getSupportLeg(){return this->support_leg;}
	walk_state getWalkState(){return this->status;}
	void plot_foot_pattern();

	std::vector<Vector3d> refzmp_list;	// 目標ZMPリスト
	std::vector<Vector2d> tpb_list;		// 目標体幹位置リスト
	std::vector<Vector2d> dpk_list;		// 目標脚配置リスト
private:
	double foot_time, foot_period;
	double dist_offset, preview_delay;

	Vector2d dP_K;
	Vector2d PFB;
	double dth_K, th_FB;
		
	leg_type support_leg;
	walk_state status;
};

#endif
