#include <iostream>
#include <vector>

#include <cmath>

#include <Eigen/Core>

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
	Vector2d dP_K(Vector2d(0.0, 0.08)), dP_K_old(Vector2d(0.0, 0.08));
	double dth_K = 0.0;
	// 蹴足の相対位置ベクトル
	Vector2d P_FB(Vector2d::Zero());
	double th_FB = 0.0;
	// 一時体幹位置ベクトル
	Vector2d dP_B(Vector2d::Zero());
	double dth_B = 0.0;

	int time_count = 0;
	const int MAX_TIME = 5;

	dpk_list.push_back(dP_K);

	// 収束ループ
	while(1){
		if(status == START){
			if(support_leg == RLEG) P_FB << 0.0, -0.08;
			else if(support_leg == LLEG) P_FB << 0.0, 0.08;
			status = WALK;
		}else if(status == WALK){
			if(support_leg == RLEG) P_FB << 0.03, -0.08;
			else if(support_leg == LLEG) P_FB << 0.03, 0.08; 
		}else if(status == STOP){
			if(support_leg == RLEG) P_FB << 0.0, -0.08;
			else if(support_leg == LLEG) P_FB << 0.0, 0.08;
		}

		if(support_leg == RLEG) support_leg = LLEG;
		else if(support_leg == LLEG) support_leg = RLEG;

		// 目標蹴足ベクトルの計算
		dP_K = tP_B + CoordinatesTransform(P_FB, tth_B);
		dth_K = tth_B + th_FB;

		cout << dP_K[0] << " " << dP_K[1] << endl; 

		dpk_list.push_back(dP_K);
		tpb_list.push_back(tP_B);

		// 一時体幹位置ベクトル
		dP_B = (dP_K + dP_K_old) / 2.0;
		//dth_B = dth_K + dthk_old / 2.0;

		dpb_list.push_back(dP_B);
		
		dP_K_old = dP_K;
		

		if(status == STOP) break;

		time_count++;
		if(MAX_TIME <= time_count) status = STOP;

		tP_B = tP_B + Vector2d(0.05, 0.0);
		tth_B += 0.0;
	}

	FILE *gp = popen("gnuplot -persist\n","w");
	fprintf(gp, "set xrange [-0.005:0.5]\n");
	fprintf(gp, "set yrange [-0.15:0.5]\n");
	fprintf(gp, "set xlabel \"x [m]\"\n");
	fprintf(gp, "set ylabel \"y [m]\"\n");
	fprintf(gp, "plot '-' with lines lw 2 lc rgb \"blue\" ,'-' with points pt 2 lc rgb \"red\",'-' with points pt 2 lc rgb \"cyan\"\n");
	for(size_t i=0;i<dpk_list.size();i++) fprintf(gp, "%f\t%f\n", dpk_list[i](0), dpk_list[i](1)); fprintf(gp,"e\n");
	for(size_t i=0;i<tpb_list.size();i++) fprintf(gp, "%f\t%f\n", tpb_list[i](0), tpb_list[i](1)); fprintf(gp,"e\n");
	for(size_t i=0;i<dpb_list.size();i++) fprintf(gp, "%f\t%f\n", dpb_list[i](0), dpb_list[i](1)); fprintf(gp,"e\n");
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
