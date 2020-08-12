#include"Init.h"



int updateDA(vector<vector<vector<vector<double>>>>&CPOP, \
			 vector<vector<vector<vector<double>>>>&DA,\
			 vector<vector<double> >&cobj, vector<vector<double> >&DAobj)
{
	int nc = CPOP.size();
	int i, j, k, n = 100;
	int flag, u;
	int lenDA = DA.size();
	int m = DAobj[0].size();  // m是目标数
	vector<int> PP;
	//double *x1 = new double[c + m], *x2 = new double[c + m];
	for (i = 0; i < CPOP.size(); i++)
	{
		flag = 0;
		vector<double > x1(m);
		vector<double > x2(m);
		j = 0;
		while (j < lenDA)  // 轮询DA里的种群
		{
			x1 = cobj[i];  // 在while里固定住某一轮的x1
			x2 = DAobj[j];
			u = dom(x1, x2, m);  // 对比哪个目标值更好
			if (u == 2)  // x1（i）轮的目标值全部大于x2轮的目标值，即x2（j）的目标值全部优于x1（i），本程序优化使所有目标值最小
			{
				flag = 1;
				break;
			}
			else if (u == 1)  // x1(i)轮的目标值全部小于x2轮的目标值，即x1(i)的目标值全部优于x2，本程序优化使所有目标值最小
			{
				DA.erase(DA.begin() + j);
				DAobj.erase(DAobj.begin() + j);  // 把x2的目标值全部擦除，j对应x2

				lenDA--;//因为擦除了一个，所以长度缩短一个
			}
			else if (u == 3)  // 各有千秋，x1轮有优于x2的目标值，x2轮也有优于x1的目标值
			{
				flag = 1;
				break;
			}
			else
			{
				j++;  // 换下一个进化结果二维向量给x2
			}
		}
		if (flag == 0)  // 如果想x1(i)轮是最优的
		{
			PP.push_back(i);  // 把最优的那个i存入PP
		}
	}
	int PP_size = PP.size();  //把最优的轮数给PP_size

	vector<vector<vector<vector<double>>>>NDA(lenDA + PP_size);  // 向量容量是所有最优的个数i+j
	vector<vector<double>>NDAobj(lenDA + PP_size);

	for (i = 0; i < lenDA + PP_size; i++)  // 轮询所有的最优，把所有的最优的种群存到NDA，对应的最优目标值存到NDAobj
	{
		NDA[i].resize(DA[0].size());
		NDAobj[i].resize(DAobj[0].size());

		if (i < lenDA)
		{
			NDA[i] = DA[i];
			NDAobj[i] = DAobj[i];

		}
		else
		{
			NDA[i] = CPOP[PP[i - lenDA]];
			NDAobj[i] = cobj[PP[i - lenDA]];

		}
	}
	lenDA = lenDA + PP.size();
	if (lenDA > n)  // 如果得到的结果比设置的种群的数量还大，就进行一下select
	{
		DAselect(NDA, NDAobj, DA, DAobj);
	}
	else {
		DA.clear(), DAobj.clear();
		DA = NDA, DAobj = NDAobj;
	}
	return 1;
}




int DAselect(vector<vector<vector<vector<double>>>>&NDA,  vector<vector<double>>&NDAobj, \
			 vector<vector<vector<vector<double>>>>&DA, vector<vector<double>>&DAobj)
{
	int i, j, LL;
	LL = NDA.size();  // 最优的种群数给LL
	int m = NDAobj[0].size();  // m是目标数量
	vector<int>a(2 * m);  // 定义一个向量，这个向量会存目标值最大的那个解决方案和目标值最小的那个解决方案
	DA.clear(), DAobj.clear();   //  先把这两个向量清空
	for (i = 0; i < m; i++)  // 轮询每个目标值
	{
		a[i] = 0;
		for (j = 1; j < LL; j++)  //固定住i，对应不同轮进化的同一目标值对比
		{
			if (NDAobj[j][i] < NDAobj[a[i]][i])  // 如果j轮的目标值更小，即j轮表现更优秀，把这个轮数存给向量a
			{
				a[i] = j;  // 存的是最小目标值的方案
			}
		}
		a[m + i] = 0;
		for (j = 1; j < LL; j++)
		{
			if (NDAobj[j][i] > NDAobj[a[m + i]][i])
			{
				a[m + i] = j;  // 存的是最大目标值的方案
			}
		}
	}
	sort(a.begin(), a.end());  // 把解决方案从小到大排序
	a.erase(unique(a.begin(), a.end()), a.end());  // 把重复的去掉，擦除
	for (i = 0; i < a.size(); i++)  // 把最大和最小的先存在DA中
	{
		DA.push_back(NDA[a[i]]);
		DAobj.push_back(NDAobj[a[i]]);
	}
	for (i = 0; i < a.size(); i++)//标记存那个最大最小是哪几个解决方案
	{
		NDA[a[i]][0][0][2] = -1;
	}
	for (i = 0; i < NDA.size(); i++)
	{
		if (NDA[i][0][0][2] == -1)  // 把存的那几个在NDA里删掉
		{
			NDA.erase(NDA.begin() + i);
			NDAobj.erase(NDAobj.begin() + i);

			--i;
		}
	}
	int N = a.size();   //NDA行数
	double W[800][20];
	double dis[800];
	double d[800];
	int t = 0; int K; double din[800];
	int iq, ip; double sum;
	double lp = 1.0 / m;
	while (NDA.size() > 0 && DA.size() < 100)
	{
		for (i = 0; i < NDA.size(); i += 1)  //要把解决方案一点点添进NDA
		{
			d[i] = INT_MAX;
			for (iq = 0; iq < N; iq += 1)
			{
				sum = 0;
				for (j = 0; j < m; j += 1)
				{
					sum += pow((fabs(DAobj[iq][j] - NDAobj[i][j])), lp);
				}
				d[i] = min(d[i], pow(sum, m));  // 取距离最小的距离放进d[i]
			}
		}
		int I;
		I = 0;
		for (i = 1; i < NDA.size(); i += 1)
		{
			if (d[I] < d[i])
			{
				I = i;
			}
		}
		vector<int>imin;
		for (i = 0; i < NDA.size(); i += 1)
		{
			if (d[i] < 0.001)
			{
				imin.push_back(i);
			}
		}
		DA.push_back(NDA[I]);
		DAobj.push_back(NDAobj[I]);

		if (imin.size() != 0)
		{
			for (i = 0; i < imin.size(); i++)
			{
				NDA[imin[i]][0][0][2] = -1;
			}
		}
		NDA[I][0][0][2] = -1;
		for (i = 0; i < NDA.size(); i++)
		{
			if (NDA[i][0][0][2] == -1)
			{
				NDA.erase(NDA.begin() + i);
				NDAobj.erase(NDAobj.begin() + i);

				i--;
			}
		}
		imin.empty();
	}
	return 1;
}