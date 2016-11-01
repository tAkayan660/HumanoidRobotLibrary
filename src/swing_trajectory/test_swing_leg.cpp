#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#include <Eigen/Core>
#include <boost/math/constants/constants.hpp>

using namespace std;
using namespace Eigen;

int main(int argc, char *argv[])
{
	ofstream writing_file;
	const float pi = boost::math::constants::pi<float>();
	/* 遊脚の時間 */
	const float period = 0.03;
	/* 目標足上げ高さ */
	const float h = 0.060;
	/* サンプリングタイム */
	const float dt = 0.01;
	int z_count=0;
	float t=0.0;

	/* 足先軌道 */
	Matrix<float,2,1> p(Matrix<float,2,1>::Zero());
	/* 目標足先接地位置 */
	Matrix<float,2,1> p_goal(Matrix<float,2,1>::Zero());
	/* 初期足先位置 */
	Matrix<float,2,1> p_start(Matrix<float,2,1>::Zero());

	/* 3次補間のための係数 */
	Matrix<float,2,4> A(Matrix<float,2,4>::Zero());

	p_goal << 0.03,0.0; p_start << 0.0, 0.0;

	/*係数を代入*/
	A << ;//???;
		
	writing_file.open("swing_foot_trajectory.csv");
	for(float t=0.0f; t<=period;t+=dt){
		/*サイクロイド曲線-＞z方向の遊脚*/
		float z_swing = ; //???

		/*3次補間-＞x,y方向の遊脚*/
		p = ;	//???
		
		/*ファイル書き込み*/
		writing_file << t << " " << p(0) << " " << p(1) << " "<<z_swing << endl;
	}
	writing_file.close();

	return 0;
}
