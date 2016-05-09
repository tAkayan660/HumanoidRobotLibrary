/*
 * @file		LinkParameter.h
 * @brief		Constant Value of Link for Humanoid Robot
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

static const double eps = numeric_limits<double>::epsilon();
static const double pi = boost::math::constants::pi<double>();

//JAXON
static const string joint_name[] = {
	"WAIST",
	"J1",
	"J2",
	"J3",
	"J4",
	"J5",
	"J6",
};

enum
{
	WAIST=0,
	J1,
	J2,
	J3,
	J4,
	J5,
	J6,
	JOINT_NUM
};

static const int parent[JOINT_NUM] = {-1,0,1,2,3,4,5};
static const int child[JOINT_NUM] = {1,2,3,4,5,6,-1};
static const int sister[JOINT_NUM] = {-1,-1,-1,-1,-1,-1,-1};

static const double LinkAxis[JOINT_NUM][3] = {
	//BASE
	{0,0,0},

	//ARM
	{0,0,1},
	{1,0,0},
	{0,0,1},
	{1,0,0},
	{0,0,1},
	{1,0,0},
};

static const double LinkPos[JOINT_NUM][3] = {
	//BASE
	{0.0f, 0.0f, 0.0f},	

	//ARM	
	{0.0f, 0.0f, 200.0f},
	{0.0f, 0.0f, 115.0f},
	{0.0f, 0.0f, 280.0f},
	{0.0f, 0.0f, 170.0f},
	{0.0f, 0.0f, 250.0f},
	{-2.5f,0.0f, 250.0f},
};

#endif
