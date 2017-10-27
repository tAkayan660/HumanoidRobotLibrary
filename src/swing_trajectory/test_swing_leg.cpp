#include <iostream>
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
	const float period = 0.30;
	/* 目標足上げ高さ */
	const float h = 0.060;
	/* サンプリングタイム */
	const float dt = 0.01; 
	
	/* 足先軌道 */
	Matrix<float,2,1> p(Matrix<float,2,1>::Zero());
	/* 目標足先接地位置 */
	Matrix<float,2,1> p_goal(Matrix<float,2,1>::Zero());
	/* 初期足先位置 */
	Matrix<float,2,1> p_start(Matrix<float,2,1>::Zero());

	/* 3次補間のための係数 */
	Matrix<float,2,4> A(Matrix<float,2,4>::Zero());

	/* 目標足先接地地点 */
	p_goal << atof(argv[1]), atof(argv[2]); 
	/* 初期の足先位置 */
	p_start << atof(argv[3]), atof(argv[4]);

	A << p_start(0), 0, 3*(p_goal(0)-p_start(0))/pow(period,2), -2*(p_goal(0)-p_start(0))/pow(period,3),
		 p_start(1), 0, 3*(p_goal(1)-p_start(1))/pow(period,2), -2*(p_goal(1)-p_start(1))/pow(period,3),
	
	writing_file.open("swing_foot_trajectory.csv");
	for(float t=0.0f; t<=period;t+=dt){
		/* z方向の遊脚軌道生成(サイクロイド曲線) */
		float z_swing = h*0.5*(1-cos(2*pi/static_cast<int>(period/dt)*(t/dt)));

		/* 時刻tのx, y方向の遊脚軌道生成 */
		p = A * Vector4f(1, t, t*t, t*t*t);
		
		/* ファイル書き込み */		
		writing_file << t << " " << p(0) << " " << p(1) << " "<<z_swing << endl;
	}
	writing_file.close();

	return 0;
}
