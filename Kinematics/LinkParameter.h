/*
 * @file		LinkParameter.h
 * @brief		Constant Value of Link for Accelite
 * @author	Ryu Yamamoto
 * @date		2016/02/26
 */

#ifndef _LINK_PARAMETER_
#define _LINK_PARAMETER_

#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <limits>
#include <boost/math/constants/constants.hpp>

using namespace std;
using namespace Eigen;

static const int ACCELITE_ELBOW = 19;
static const int ACCELITE = 17;

static const double eps = numeric_limits<double>::epsilon();
static const double pi = boost::math::constants::pi<double>();

static const string joint_name[] = {
	"WAIST",
	"HIP_YAW_L",
	"HIP_ROLL_L",
	"HIP_PITCH_L",
	"KNEE_PITCH_L",
	"FOOT_PTICH_L",
	"FOOT_ROLL_L",
	"HIP_YAW_R",
	"HIP_ROLL_R",
	"HIP_PITCH_R",
	"KNEE_PITCH_R",
	"FOOT_PITCH_R",
	"FOOT_ROLL_R",	
};

enum
{
	WAIST=0,
	HIP_YAW_L,
	HIP_ROLL_L,
	HIP_PITCH_L,
	KNEE_PITCH_L,
	FOOT_PITCH_L,
	FOOT_ROLL_L,
	HIP_YAW_R,
	HIP_ROLL_R,
	HIP_PITCH_R,
	KNEE_PITCH_R,
	FOOT_PITCH_R,
	FOOT_ROLL_R,
	LEG_JOINT_NUM
};

enum LegType
{
	PARALLEL_LINK=0,
	SERIAL_LINK
};

static const int parent[LEG_JOINT_NUM] = {-1,0,1,2,3,4,5,0,7,8,9,10,11};
static const int child[LEG_JOINT_NUM] = {1,2,3,4,5,6,-1,8,9,10,11,12,-1};
static const int sister[LEG_JOINT_NUM] = {-1,-1,7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

static const double LinkAxis[LEG_JOINT_NUM][3] = {
	{0,0,0},	//WASIT
	{0,0,1},
	{1,0,0},
	{0,1,0},
	{0,1,0},
	{0,1,0},
	{1,0,0},
	{0,0,1},
	{1,0,0},
	{0,1,0},
	{0,1,0},
	{0,1,0},
	{1,0,0},
};

//For Accelite
/*
static const double LinkPos[LEG_JOINT_NUM][3] = {
	{0,0,0},			//WAIST
	{0,44.0f,0},		//HIP_YAW_L
	{0.0,0.0,-42.8f},	//HIP_ROLL_L
	{15.0f,0.0,0.0},	//
	{0.0,0.0,-105.0f},	
	{0.0,0.0,-41.0f},
	{0.0,0.0,-105.0f},
	{0,-44.0f,0},
	{},
	{},
	{},
	{},
	{}
};
*/

//For test
static const double LinkPos[LEG_JOINT_NUM][3] = {
	{0.0f, 0.0f, 0.0f},		//WAIST
	{0.0f, -50.0f, 0.0f},	//HIP_YAW_L
	{0.0f, 0.0f, -0.0f},	//HIP_ROLL_L
	{0.0f, 0.0f, 0.0f},		//HIP_PITCH_L
	{0.0f, 0.0f, -100.0f},	//KNEE_PITCH_L
	{0.0f, 0.0f, -100.0f},	//FOOT_PITCH_L
	{0.0f, 0.0f, 0.0f},		//FOOT_ROLL_L
	{0.0f, 50.0f, 0.0f},	//HIP_YAW_R
	{0.0f, 0.0f, -0.0f},	//HIP_ROLL_R
	{0.0f, 0.0f, 0.0f},		//HIP_PITCH_R
	{0.0f, 0.0f, -100.0f},	//KNEE_PITCH_R
	{0.0f, 0.0f, -100.0f},	//FOOT_PITCH_R
	{0.0f, 0.0f, 0.0f},		//FOOT_ROLL_R
};

#endif
