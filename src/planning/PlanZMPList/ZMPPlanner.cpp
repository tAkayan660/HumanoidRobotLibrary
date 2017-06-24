#include "ZMPPlanner.h"

double deg2rad(double degree)
{
	return degree * M_PI / 180.0;
}

ZMPPlanner::ZMPPlanner(double _foot_period, double _dist_offset)
	: foot_period(_foot_period), foot_time(_foot_period/2.0f), preview_delay(2.0),
		dist_offset(_dist_offset), support_leg(RLEG), status(START),
		dP_K(Vector2d::Zero())
{
	dpk_list.push_back(dP_K);
//	refzmp_list.push_back(Vector3d(0.0, 0.0, 0.0));
}

// 座標変換(2D)
Vector2d ZMPPlanner::CoordinatesTransform(Vector2d vec, double th)
{
	Vector2d trans_vec(Vector2d::Zero());

	trans_vec[0] = vec[0] * cos(deg2rad(th)) - vec[1] * sin(deg2rad(th));
	trans_vec[1] = vec[0] * sin(deg2rad(th)) + vec[1] * cos(deg2rad(th));

	return trans_vec;
}

// 次の目標体幹位置に対する目標脚位置
void ZMPPlanner::getNextZMP(Vector2d tP_B, double tth_B)
{
	shiftFootVec();

	dP_K = tP_B + CoordinatesTransform(PFB, tth_B);
	dth_K = tth_B + th_FB;

	tpb_list.push_back(tP_B);
	dpk_list.push_back(dP_K);

	Vector2d temp_refzmp;
	temp_refzmp(0) = (dpk_list[dpk_list.size()-1](0) - dpk_list[dpk_list.size()-2](0))/2;
	temp_refzmp(1) = (dpk_list[dpk_list.size()-2](1) - dpk_list[dpk_list.size()-2](1))/2;

	refzmp_list.push_back(Vector3d(foot_time, dP_K[0], dP_K[1]));

	if(status == STOP){
		foot_time += foot_period / 2.0f;
	}else{
		foot_time += foot_period;
	}

	if(status == START) status = WALK;

	if(status == STOP){
		dpk_list.push_back(tP_B);
		refzmp_list.push_back(Vector3d(foot_time, tP_B[0], tP_B[1]));
		refzmp_list.push_back(Vector3d(foot_time+preview_delay, tP_B[0], tP_B[1]));	// For Preview Control
	}
}

// 目標体幹位置における脚先の相対位置
void ZMPPlanner::shiftFootVec()
{
	if(support_leg == RLEG){
		support_leg = LLEG;
		PFB << 0.0, -dist_offset;
	}else if(support_leg == LLEG){
		support_leg = RLEG;
		PFB << 0.0, dist_offset;
	}
}

// フットプリントをプロット
void ZMPPlanner::plot_foot_pattern()
{
	FILE *gp = popen("gnuplot -persist\n","w");
	//fprintf(gp, "set xrange [-0.005:0.65]\n");
	//fprintf(gp, "set yrange [-0.15:0.8]\n");
	fprintf(gp, "set xlabel \"x [m]\"\n");
	fprintf(gp, "set ylabel \"y [m]\"\n");
	fprintf(gp, "plot '-' with lines lw 2 lc rgb \"blue\" title \"reference ZMP\",'-' with points pt 2 lc rgb \"red\" title \"Torso Position\"\n");
	for(size_t i=0;i<refzmp_list.size();i++) fprintf(gp, "%f\t%f\n", refzmp_list[i](1), refzmp_list[i](2)); fprintf(gp,"e\n");
	for(size_t i=0;i<tpb_list.size();i++) fprintf(gp, "%f\t%f\n", tpb_list[i](0), tpb_list[i](1)); fprintf(gp,"e\n");
	fprintf(gp,"exit\n");
	pclose(gp);
}

