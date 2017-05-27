#include <iostream>
#include <vector>

#include <cmath>

#include <Eigen/Core>

#include "PreviewControl.h"

using namespace std;
using namespace Eigen;

enum leg_type{RLEG=-1, LLEG=1, BOTH=0};
enum walk_type{START, WALK, STOP};

double deg2rad(double degree)
{
	double radian = degree * M_PI / 180.0;
	return radian;
}

double rad2deg(double radian)
{
	double degree = radian * 180.0 / M_PI;
	return radian;
}
Vector2d CoordinatesTransform(Vector2d vec, double th);

int main(int argc, char *argv[])
{
	preview_control preview_node(0.01, 1.6, 0.26);

	leg_type support_leg = RLEG;
	walk_type status = START;

	vector<Vector2d> tpb_list;	// 体幹位置リスト
	vector<Vector2d> dpk_list;	// 蹴足位置リスト
	vector<Vector2d> dpb_list;	// 一時体幹位置リスト

	vector<double> tthb_list;
	vector<double> dthk_list;
	vector<double> dthb_list;

	// 体幹位置ベクトル
	Vector2d tP_B(Vector2d::Zero());
	double tth_B = 0.0;
	// 目標蹴脚ベクトル
	Vector2d dP_K(Vector2d(0.0, 0.0)), dP_K_old(Vector2d(0.0, 0.0));
	double dth_K = 0.0, dthk_old = 0.0;
	// 蹴足の相対位置ベクトル
	Vector2d P_FB(Vector2d::Zero());
	double th_FB = 0.0;
	// 一時体幹位置ベクトル
	Vector2d dP_B(Vector2d::Zero());
	double dth_B = 0.0;

	int time_count = 0;
	const int MAX_TIME1 = 3;
	const int MAX_TIME2 = 8;
	const int MAX_TIME3 = 15;

	double time = 0.0;
	double half_period = 0.32;
	vector<Vector3d> refzmp_list;

	dpk_list.push_back(dP_K);
	refzmp_list.push_back(Vector3d(time, dP_K[0], dP_K[1]));

	time = 0.32;
	// 収束ループ
	while(1){
		if(status == START){
			if(support_leg == RLEG) P_FB << 0.0, -0.04;
			else if(support_leg == LLEG) P_FB << 0.0, 0.04;
			status = WALK;
		}else if(status == WALK){
			if(support_leg == RLEG) P_FB << 0.01, -0.04;
			else if(support_leg == LLEG) P_FB << 0.01, 0.04; 
		}else if(status == STOP){
			if(support_leg == RLEG) P_FB << 0.0, -0.04;
			else if(support_leg == LLEG) P_FB << 0.0, 0.04;
		}

		if(support_leg == RLEG) support_leg = LLEG;
		else if(support_leg == LLEG) support_leg = RLEG;

		// 目標蹴足ベクトルの計算
		dP_K = tP_B + CoordinatesTransform(P_FB, tth_B);
		dth_K = tth_B + th_FB;

		dpk_list.push_back(dP_K);
		tpb_list.push_back(tP_B);

		// 一時体幹位置ベクトル
		dP_B = (dP_K + dP_K_old) / 2.0;
		dth_B = dth_K + dthk_old / 2.0;

		dpb_list.push_back(dP_B);

		// 目標ZMPリスト
		refzmp_list.push_back(Vector3d(time, dP_K[0], dP_K[1]));
		time += half_period;
		
		dP_K_old = dP_K;
		dthk_old = dth_K;

		if(status == STOP) break;

		time_count++;
		if(MAX_TIME3 <= time_count) status = STOP;

		if(time_count < MAX_TIME1){
			tP_B = tP_B + Vector2d(0.03, 0.0);
			tth_B += 0.0;
		}else if(MAX_TIME1 <= time_count && time_count < MAX_TIME2){
			tP_B = tP_B + Vector2d(0.03, 0.03);
			tth_B += 0.0;
		}else if(MAX_TIME2 <= time_count && time_count <= MAX_TIME3){
			tP_B = tP_B + Vector2d(0.03, -0.03);
			tth_B -= 0.0;
		}
	}
	
	dpk_list.push_back(tP_B);
	refzmp_list.push_back(Vector3d(time+2.0-0.32,tP_B[0], tP_B[1]));

	preview_node.interpolation_zmp_trajectory(refzmp_list);

	vector<Vector2d> com_pos_list;
	Vector2d com_pos, com_vel, com_acc;
	while(preview_node.update(com_pos, com_vel, com_acc)){
		com_pos_list.push_back(com_pos);
	}

	FILE *gp = popen("gnuplot -persist\n","w");
	fprintf(gp, "set xrange [-0.005:0.65]\n");
	fprintf(gp, "set yrange [-0.15:0.8]\n");
	fprintf(gp, "set xlabel \"x [m]\"\n");
	fprintf(gp, "set ylabel \"y [m]\"\n");
	fprintf(gp, "plot '-' with lines lw 2 lc rgb \"blue\" ,'-' with points pt 2 lc rgb \"red\",'-' with points pt 2 lc rgb \"cyan\", '-' with lines lw 2 lc rgb \"green\" \n");
	for(size_t i=0;i<dpk_list.size();i++) fprintf(gp, "%f\t%f\n", dpk_list[i](0), dpk_list[i](1)); fprintf(gp,"e\n");
	for(size_t i=0;i<tpb_list.size();i++) fprintf(gp, "%f\t%f\n", tpb_list[i](0), tpb_list[i](1)); fprintf(gp,"e\n");
	for(size_t i=0;i<dpb_list.size();i++) fprintf(gp, "%f\t%f\n", dpb_list[i](0), dpb_list[i](1)); fprintf(gp,"e\n");
	for(size_t i=0;i<com_pos_list.size();i++) fprintf(gp, "%f\t%f\n", com_pos_list[i](0), com_pos_list[i](1)); fprintf(gp,"e\n");
	fprintf(gp,"exit\n");
	pclose(gp);

	return 0;
}

Vector2d CoordinatesTransform(Vector2d vec, double th)
{
	Vector2d trans_vec(Vector2d::Zero());

	trans_vec[0] = vec[0] * cos(deg2rad(th)) - vec[1] * sin(deg2rad(th));
	trans_vec[1] = vec[0] * sin(deg2rad(th)) + vec[1] * cos(deg2rad(th));

	return trans_vec;
}
