#include"Init.h"

/******���ȡһ����С�����֮���һ��ֵ********/
template <class numtype>
numtype rand(numtype min, numtype max)
{
	srand((unsigned)time(NULL));
	return min + (max - min) * rand() / (RAND_MAX + 1.0);
}

/* ���ֵΪmiu������Ϊsigma����̫�ֲ�������x���ĺ���ֵ*/
double normal(double x, double miu, double sigma)
{
	return 1.0 / sqrt(2.0 * M_PI) / sigma * exp((-1.0 * pow((x - miu),2)) / (2.0 * pow(sigma,2)));  //��ʽ����֤
}

/*���յ����������ں���ֵ��������λ�÷ֲ�����õ���̫����xֵ*/
double randn(double miu, double sigma, double min, double max)// ���㷨��ʵ�ʽ���͹�ʽ�����
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
