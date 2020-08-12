#include"Init.h"


vector<vector<vector<vector<double>>>> find_nodom_ai(vector<vector<vector<vector<double>>>>&POP, \
												  vector<vector<double>>&obj, \
												  vector<vector<double>>&DAobj, int m)
{
	int i, j; i = 0;
	int z;
	int k;
	vector<vector<vector<vector<double>>>> DA(POP);  // 复制一个种群副本给DA
	//vector<double> a(c + m), b(c + m);
	vector<double>a(m), b(m); // 两个目标向量
	while (i < DA.size())  // 轮询DA中所有的类，两个while的嵌套是为了实现DA里所有的种群都两两对比，把最优的种群留下，其他都擦除
	{
		int flag = 0;
		j = i + 1;
		a = DAobj[i];  // 把第(i+1)次得到的目标值给a
		while (j < DA.size())  // 轮询DA中所有的种群，从第二个种群开始，这个while为了固定住a轮目标值，用其他目标值都和a轮对比
		{
			b = DAobj[j];  // 把第(j+1)次得到的目标值给b，第一次的while循环是b轮是a轮的下一轮
			z = dom(a, b, m);  // 三个形参，分别是某一轮的目标值a，某一轮的目标值b，（a轮在b轮之前）和目标个数m，判断a这一轮和b这一轮目标值的异同
			if (z == 2)  // a轮的目标值全部大于b轮的目标值
			{
				flag = 1;
				break;
			}
			else if (z == 3)  // a轮的目标值全部等于b轮的目标值
			{
				DA.erase(DA.begin() + j);
				DAobj.erase(DAobj.begin() + j);  // 擦除这一次的DA，即多样性存档

			}
			else if (z == 1)  // a轮的目标值全部小于b轮的目标值
			{
				DAobj.erase(DAobj.begin() + j);
				DA.erase(DA.begin() + j);   // 擦除这一次的DA多样性存档，a轮的更小，所以把b轮的擦除掉，j是b轮的下标

			}
			else  // a轮的目标值和b轮的目标值是其他关系
			{
				j++;
			}
		}
		if (flag == 1)  //while里有a轮被淘汰的情况，则把a也在DA中擦除
		{
			DA.erase(DA.begin() + i);
			DAobj.erase(DAobj.begin() + i);

		}
		else // 否则换固定下一个i
		{
			i++;
		}
	}
	return DA;//就是把这次的n轮的进化中最优的那个种群留在了里面
}