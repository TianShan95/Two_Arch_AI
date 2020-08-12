#include"Init.h"


/*
*这个函数是在对比两次的目标值
*Is a这一轮的目标值全部优于b轮
*or b这一轮的目标值全部优于a轮
*or a这一轮和b这一轮的目标值全部相同
*or others
*/

int dom(vector<double>&a, vector<double>&b, int m)
{
	int i, t = 0, p = 0, q = 0, z;
	for (i = 0; i < m; i++)  // 轮询每个目标值
	{
		if (a[i] <= b[i])   // 如果a这轮的目标值小于b轮的目标值，t自加1
		{
			t++;
		}
		if (a[i] >= b[i])  // 如果a这轮的目标值大于b轮的目标值，q自加1
		{
			q++;
		}
		if (a[i] == b[i])  // 如果a这轮的目标值等于b轮的目标值，p自加1
		{
			p++;
		}
	}
	if (t == m && p != m)  // 如果for循环里每次都是a轮的目标值小于b轮的目标值，即每次都是t自加1，则z为1
	{
		z = 1;
	}
	else if (q == m && p != m) // 如果for循环里每次都是a轮的目标值大于b轮的目标值，即每次都是q自加1，则z为2
	{
		z = 2;
	}
	else if (p == m)// 如果for循环里每次都是a轮的目标值等于b轮的目标值，即每次都是p自加1，则z为3
	{
		z = 3;
	}
	else           // 其他情况，则z为4
	{
		z = 4;
	}
	return z;
}