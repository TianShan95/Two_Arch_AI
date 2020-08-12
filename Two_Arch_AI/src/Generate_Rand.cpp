#include"Init.h"

/******随机取一个最小和最大之间的一个值********/
template <class numtype>
numtype rand(numtype min, numtype max)
{
	srand((unsigned)time(NULL));
	return min + (max - min) * rand() / (RAND_MAX + 1.0);
}

/* 求均值为miu，方差为sigma的正太分布函数在x处的函数值*/
double normal(double x, double miu, double sigma)
{
	return 1.0 / sqrt(2.0 * M_PI) / sigma * exp((-1.0 * pow((x - miu),2)) / (2.0 * pow(sigma,2)));  //公式已验证
}

/*按照到矩形区域在函数值曲线上下位置分布情况得到正太函数x值*/
double randn(double miu, double sigma, double min, double max)// 简单算法，实际结果和公式法差不多
{
	double x, y, dScope;
	do
	{
		x = rand(min, max);
		y = normal(x, miu, sigma);
		dScope = rand(0.0, normal(miu, miu, sigma));
	} while (dScope > y);
	return x;
}
