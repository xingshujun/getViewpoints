// VIEWPOINTGET.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>

//  坐标系以左上角为(0,0)点
//  SubPixelNumPerPitch 这个线数是指光栅每个截距下覆盖的子像素数，是光栅的固有属性，
//                      光栅确定了，它的属性就确定了
//  tanIncAngle         是光栅与y轴夹角的正切值
//  

#define PI 3.141592654
#define DegToRad(DegValue) (DegValue * (PI / 180)) 

int getViewNO(int i, int j, int k, int totalViewCount, float tanIncAngle, float SubPixelNumPerPitch)
{
	float step_value = SubPixelNumPerPitch / totalViewCount;
	float value_pixel = 3 * j + 3 * i* tanIncAngle + k;
	float judge_value = value_pixel - int(value_pixel / SubPixelNumPerPitch) * SubPixelNumPerPitch;

	if (0 > judge_value)
	{
		judge_value = judge_value + SubPixelNumPerPitch;
	}

	int view_point_number = totalViewCount - std::floor(judge_value / step_value) - 1;
	return view_point_number;
}

int main()
{
	std::string filename = "output.txt";

	std::ofstream outfile;
	outfile.open(filename.c_str(), std::ofstream::out);

	int totalViewCount = 16;
	float  angle = 14.04;
	float  incAngleTan = std::tan(DegToRad(angle));

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				outfile << getViewNO(i, j, k, totalViewCount, incAngleTan, 4 * std::cos(DegToRad(angle))) << "\t";
			}
		}
		outfile << "\n";
	}

	if (!outfile)
	{
		throw std::runtime_error("file cannot open");
		return -1;
	}
	else
	{
		outfile << " " << std::endl;
	}

	outfile.close();
	return 0;
}