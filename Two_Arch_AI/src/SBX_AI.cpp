#include"Init.h"


int Round(double num) {
	return num > 0.0 ? (num + 0.5) : (num - 0.5);
}
int notFiniteNumber1(double d)  // 不正常返回1，正常（为正常的浮点数或者0）返回0
{
	switch (fpclassify(d)) {
	case FP_INFINITE:  return 1;  // d是正负无穷 
	case FP_NAN:       return 1;  // d不是一个数
	case FP_ZERO:      return 0;  // d为0
	case FP_SUBNORMAL: return 1;  // d太小以至于不能用浮点数的规格化形式表示
	case FP_NORMAL:	   return 0;  // 为正常的浮点数
	}
}

/*
*SBX:模拟二进制交叉（Simulated binary crossover),需要随机选择两个父代
*这个应该是进化函数，cpop也就是进化子代就是从这个函数产生的
*/
vector<vector<vector<vector<double>>>> SBXAI(vector<vector<vector<vector<double>>>>&CA, \
	vector<vector<vector<vector<double>>>>&DA, vector<vector<double>>&CAobj, \
	   vector<vector<double> >&DAobj, int n, int m, double* Num_Of_Core_Per_ES)
{
	int i, j;
	vector<vector<vector<vector <double>>>> npop(2 * n);  // 定义一个4维向量npop(continue population)，容量是两倍的解集
	vector<vector<vector<vector <double>>>> ES_Mark(2 * n);  // 这个容器存放计算出来的那个数
	
	for (i = 0; i < 2 * n; i += 1)   // 给npop分配空间
	{
		ES_Mark[i].resize(CA[0].size());
		npop[i].resize(CA[0].size());
		for (j = 0; j < CA[0].size(); ++j) {
			npop[i][j].resize(CA[0][0].size());  // npop[][]可以访问到第几类
		}
	}
	int lenDA = DA.size();  // 变量lenDA存放着DA多样性存档的种群数量
	int K, Y;
	double eta_c = 15.0; double yd, yu, expp, y1, y2;
	double beta, alpha, betaq, chld1, chld2, aa, bb;
	vector<double> do1(m), do2(m);
	srand((unsigned)time(0));
	for (i = 0; i < n; i++)  // 轮询CA的第n个种群---------------------------------------------------------first for
	{
		int k1 = rand() % CA.size();
		int k2 = rand() % CA.size();
		while (k1 == k2) { k2 = rand() % CA.size(); }  // 产生两个不同的随机数，CA是pop总种群
		/***随机选择两次进化的目标向量，分别命名为do1，do2**/
		do1 = CAobj[k1];
		do2 = CAobj[k2];
		int z = dom(do1, do2, m);  // 这个返回的z表示了do1，do2这两次进化后的目标值的对比结果

		/* do1轮的目标值全部小于do2轮的目标值,也就是下标为k1的目标向量值全部碾压下标为k2的目标值，K取优秀的下标
		*如果不是所有目标值全部碾压，则随机的方式确定K是取k1还是k2
		*/
		if (z == 1) { K = k1; }  
		else if (z == 2) { K = k2; }
		else if (((double)rand() / RAND_MAX) <= 0.5) { K = k1; }
		else { K = k2; }
		Y = rand() % lenDA;  // 产生一个随机数，为了下面for循环随机选择种群用的

		for (int u = 0; u < CA[0].size(); ++u)   // 轮询CA的每个种群的每个类------------------------------second for
		{
			yd = 0; // 下界
			yu = 1; // 上界

			//vector<int> PAR1(DA[0][0].size());PAR1 = DA[Y][u];
			//vector<int> PAR2(CA[0][0].size());PAR2 = CA[K][u];
			for (j = 0; j < CA[0][0].size(); ++j) // 轮询CA每个种群的每个类的每个个体-------------------------third for
			{
				/**取出随机的两个种群，取出两个种群对应类的对应个体的ES标志位**/
				int par1 = DA[Y][u][j][2];  
				int par2 = CA[K][u][j][2];

				double r2 = (double)rand() / RAND_MAX;  //产生一个0-1之间的随机数

				if (r2 <= 0.5)  // 这是表示有一半的概率会发生if里的变化
				{
					y1 = min(par1, par2), y2 = max(par1, par2);

					if ((y1 - yd) > (yu - y2)) 
					{
						beta = 1.0 + 2 * (yu - y2) / (y2 - y1);
					}
					else 
					{
						beta = 1.0 + 2 * (y1 - yd) / (y2 - y1);
					}
						
					expp = eta_c + 1.0; beta = 1.0 / beta; alpha = 2.0 - pow(beta, expp);

					double r3 = (double)rand() / RAND_MAX;

					if (r3 <= 1.0 / alpha) 
					{
						alpha = alpha * r3;
						expp = 1.0 / (eta_c + 1.0);
						betaq = pow(alpha, expp);
					}
					else 
					{
						alpha = 1.0 / (2.0 - alpha * r3);
						expp = 1.0 / (eta_c + 1.0);
						betaq = pow(alpha, expp);
					}

					chld1 = 0.5*((y1 + y2) - betaq * (y2 - y1));
					chld2 = 0.5*((y1 + y2) + betaq * (y2 - y1));
					aa = max(chld1, yd);
					bb = max(chld2, yd);
					aa = min(aa, yu);
					bb = min(bb, yu);

					if (notFiniteNumber1(aa)) {  // 如果aa不正常则以随机的概率选择aa是0还是1
						if ((double)rand() / RAND_MAX <= 0.5) { aa = yu; }
						else { aa = yd; }
					}
					if (notFiniteNumber1(bb)) {  // 如果bb不正常则以随机的概率选择aa是0还是1
						if ((double)rand() / RAND_MAX <= 0.5){bb = yu;}
						else { bb = yd; }
					}
					ES_Mark[2 * i][u][j][2] = Round(aa);  // 把aa，bb的值存到ES_Mark里
					ES_Mark[2 * i + 1][u][j][2] = Round(bb);
				}
				else {
					ES_Mark[2 * i][u][j][2] = par1;
					ES_Mark[2 * i + 1][u][j][2] = par2;
				}
			}  // loop j
		}  // loop u
		if (!Constraint(npop[2 * i], Num_Of_Core_Per_ES))   // 如果这个解不符合限制
		{
			npop[2 * i] = DA[Y];
			ES_Mark[2 * i] = CA[Y];
		}
		if (!Constraint(npop[2 * i + 1], Num_Of_Core_Per_ES))   // 如果这个解不符合限制，就把原来随机取得放进去
		{
			npop[2 * i + 1] = DA[K];
			ES_Mark[2 * i + 1] = CA[K];
		}
	}  // loop i
	return npop;
}