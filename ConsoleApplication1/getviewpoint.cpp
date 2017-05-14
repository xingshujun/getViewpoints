// VIEWPOINTGET.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <fstream>

//  ����ϵ�����Ͻ�Ϊ(0,0)��
//  SubPixelNumPerPitch ���������ָ��դÿ���ؾ��¸��ǵ������������ǹ�դ�Ĺ������ԣ�
//                      ��դȷ���ˣ��������Ծ�ȷ����
//  tanIncAngle         �ǹ�դ��y��нǵ�����ֵ
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