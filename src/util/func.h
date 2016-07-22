#ifndef FUNC_H
#define FUNC_H

double rad2deg(double radian)
{
	double degree = radian * 180.0f / pi;
	return degree;
}

double deg2rad(double degree)
{
	double radian = degree * pi / 180.0f;
	return radian; 
}

#endif
