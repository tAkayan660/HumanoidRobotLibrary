#include "FootStepPlanner.h"

const int MAX_STEP = 15;

int main(int argc, char *argv[])
{
	int count = 0;
	Vector2d tP_B(Vector2d::Zero());
	double tth_B = 0.0;

	FootStepPlanner plan_node(0.32, 0.04);

	while(1){
		// 一歩分の蹴足位置と目標ZMPを取得
		plan_node.getNextStep(tP_B, tth_B);

		// 停止判定
		if(plan_node.getWalkState() == STOP) break;

		// 指定の歩数歩いたら終了
		count++;
		if(MAX_STEP <= count) plan_node.setStopFlag();

		// 体幹位置を一歩分移動
		tP_B += Vector2d(0.03, 0.03); tth_B += 5.0;
	}

	plan_node.plot_foot_pattern();
}
