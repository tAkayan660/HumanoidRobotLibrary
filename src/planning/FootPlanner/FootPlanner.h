/*
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2016, RDC Lab and Chiba Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _FootPlanner_H_
#define _FootPlanner_H_

#include <iostream>
#include <vector>

#include <Eigen/Core>

#include "PlanCommon.h"

using namespace std;
using namespace Eigen;

class FootPlanner{
	private:
		const double dt;
		double time, step_time;
		double zmp_correct_y, one_step_stride;
		int foot_step_count;
		double target_distance;
		FootStatus next_leg_support;
		WalkingStatus walking_status;
		Pos2D stride, target_pos, control_point, next_control_point;
	public:
		vector<Vector4d> foot_step_list;
	public:
		FootPlanner(const double _dt, const double _step_time)
			: dt(_dt), step_time(_step_time), foot_step_count(0)
		{}
		bool SetTargetPos(const double target_x, const double target_y, const double target_th, FootStatus ref_leg_sup, WalkingStatus ref_walking_status);
		bool target_pos_2_foot_step(FootStatus ref_leg_sup);
		double DistanceTargetPos(Pos2D current_pos);
		void SetFootStepParameter(const double stride_x, const double stride_y, const double stride_th, const double zmp_correct_y, const double step_time)
		{
			stride.x  = stride_x;
			stride.y  = stride_y;
			stride.th = stride_th;

			this->zmp_correct_y = zmp_correct_y;
			this->step_time		= step_time;

			one_step_stride = sqrt(pow(stride.x, 2) + pow(stride.y, 2));
		}
		void foot_step_list_clear()
		{
			foot_step_list.clear();
			foot_step_count = 0;
		}
		void start_walk(FootStatus ref_leg_sup);
		void stop_walk();
};

#endif
