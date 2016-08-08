#include "PreviewControl.h"
#include "matplotlibcpp.h"

using namespace MotionControl;
namespace plt = matplotlibcpp;

int main(int argc, char *argv[])
{
	bool result=true;
	Vector2f com_pos, com_vel, com_acc;
	vector<Vector4f> foot_step_list;
	vector<float> cog_list_x, cog_list_y;
	vector<float> refzmp_x, refzmp_y;

	/* 予見制御クラス */
	ZMPPreviewControl preview_control(0.01, 1.0);
	
	/* 予見制御システムを拡大系で扱う */
	preview_control.ExtendPreviewControlParam();

	/* 目標ZMPを与える */
	foot_step_list.push_back(Vector4f(0.0,0.0,0.0,0.0));
	foot_step_list.push_back(Vector4f(0.3,0.0,0.05,0.0));
	foot_step_list.push_back(Vector4f(0.6,0.01,-0.05,0.0));
	foot_step_list.push_back(Vector4f(0.9,0.02,0.05,0.0));
	foot_step_list.push_back(Vector4f(1.2,0.02,0.0,0.0));
	foot_step_list.push_back(Vector4f(3.2,0.02,0.0,0.0));
	
	/* 目標ZMP軌道の補間 */
	preview_control.RefZmpTrajectory(foot_step_list);
	
	/* 予見制御計算ループ */	
	while(result){
		result = preview_control.calc_xk(com_pos, com_vel, com_acc);
		cog_list_x.push_back(com_pos(0));
		cog_list_y.push_back(com_pos(1));
	}
	
	/* グラフ描画用 */	
	for(size_t i=0;i<preview_control.refzmp.size();i++)
	{
		refzmp_x.push_back(preview_control.refzmp[i](0));
		refzmp_y.push_back(preview_control.refzmp[i](1));
	}	

	/* 歩行パターン軌道描画 */
	plt::title("Preview Control");
	plt::xlabel("x[m]");
	plt::ylabel("y[m]");
	plt::xlim(-0.01, 0.03);
	plt::ylim(0.16, -0.16);
	plt::named_plot("Reference ZMP", refzmp_x, refzmp_y, "-r");
	plt::named_plot("Center of Mass", cog_list_x, cog_list_y, "-g");
	plt::legend();
	plt::show();
}
