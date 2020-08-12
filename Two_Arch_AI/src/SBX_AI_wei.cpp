#include"Init.h"
int Round(double num) {
	return num > 0.0 ? (num + 0.5) : (num - 0.5);
}
int notFiniteNumber1(double d)
{
	switch (fpclassify(d)) {
	case FP_INFINITE:  return 1;
	case FP_NAN:       return 1;
	case FP_ZERO:      return 0;
	case FP_SUBNORMAL: return 1;
	case FP_NORMAL:	   return 0;
	}
}


vector<vector<vector<vector<double>>>> SBXAI(vector<vector<vector<vector<double>>>>&CA, vector<vector<vector<vector<double>>>>&DA, \
								  vector<vector<int>>&CAYU, vector<vector<int>>&DAYU, vector<vector<double>>&CAobj,\
								  vector<vector<double>>&DAobj,vector<vector<int>>&cyu,int n,int m, vector<double>&buv, \
								  vector<double>&cu, vector<vector<double>>&cuv, vector<vector<double>>&nuv)
{
	int i, j;
	vector<vector<vector<vector<double>>>>npop(2 * n);
	cyu.resize(2 * n);
	for (i = 0; i < 2 * n; i += 1) // 初始化容量
	{
		npop[i].resize(CA[0].size());
		cyu[i].resize(CAYU[0].size());
		for (j = 0; j < CA[0].size(); ++j) 
		{
			npop[i][j].resize(CA[0][0].size());
		}
	}
	int lenDA = DA.size();
	int K, Y;
	double eta_c = 15.0; double yd, yu, expp, y1, y2;
	double beta, alpha, betaq, chld1, chld2, aa, bb;
	vector<double> do1(m), do2(m);
	srand((unsigned)time(0));
	for (i = 0; i < n; i++) {
		int k1 = rand() % CA.size();  // 产生随机数k1,k2，是为了随机选出某一轮进化出的结果
		int k2 = rand() % CA.size();
		while (k1 == k2) { k2 = rand() % CA.size(); }  // k1和k2需要是不同的随机数
		do1 = CAobj[k1];  //根据随机数k1和k2选出某一轮进化后计算所得的目标值
		do2 = CAobj[k2];
		int z = dom(do1, do2, m);  // 对比两轮进化后的目标值do1，do2的优劣


		/* do1轮的目标值全部小于do2轮的目标值,也就是下标为k1的目标向量值全部碾压下标为k2的目标值，K取优秀的下标
		*如果不是所有目标值全部碾压，则随机的方式确定K是取k1还是k2, K取最优的k值 
		*/
		if (z == 1) { K = k1; }  // do1轮的目标值全部小于do2轮的目标值
		else if (z == 2) { K = k2; }
		else if (((double)rand() / RAND_MAX) <= 0.5) { K = k1; }
		else { K = k2; }


		Y = rand() % lenDA;  // 随机抽取一个种群（解决方案）
		for (j = 0; j < CAYU[0].size(); j++) {
			int par1 = DAYU[Y][j];
			int par2 = CAYU[K][j];
			yu = 1.0, yd = 0;
			double r2 = (double)rand() / RAND_MAX;
			if (r2 <= 0.5) {
				y1 = min(par1, par2), y2 = max(par1, par2);
				if ((y1 - yd) > (yu - y2)) {
					beta = 1.0 + 2 * (yu - y2) / (y2 - y1);
				}
				else {
					beta = 1.0 + 2 * (y1 - yd) / (y2 - y1);
				}
				expp = eta_c + 1.0; beta = 1.0 / beta; alpha = 2.0 - pow(beta, expp);
				double r3 = (double)rand() / RAND_MAX;
				if (r3 <= 1.0 / alpha) {
					alpha = alpha*r3;
					expp = 1.0 / (eta_c + 1.0);
					betaq = pow(alpha, expp);
				}
				else {
					alpha = 1.0 / (2.0 - alpha*r3);
					expp = 1.0 / (eta_c + 1.0);
					betaq = pow(alpha, expp);
				}
				chld1 = 0.5*((y1 + y2) - betaq*(y2 - y1));
				chld2 = 0.5*((y1 + y2) + betaq*(y2 - y1));
				aa = max(chld1, yd);
				bb = max(chld2, yd);
				aa = min(aa, yu);
				bb = min(bb, yu);
				if (notFiniteNumber1(aa)){
					if ((double)rand() / RAND_MAX <= 0.5) {aa = yu;}
					else {aa = yd;}
				}
				if (notFiniteNumber1(bb)) {
					if ((double)rand() / RAND_MAX <= 0.5) { bb = yu; }
					else { bb = yd; }
				}
				cyu[2 * i][j] = Round(aa);
				cyu[2 * i+1][j] = Round(bb);
			}//r2
			else {
				cyu[2 * i][j] = par1;
				cyu[2 * i + 1][j] = par2;
			}
		}//j 


		for (int u = 0; u < CA[0].size(); ++u) {
			yu = CAYU[0].size() - 1;//nodesize
			yd = 0;
			//vector<int> PAR1(DA[0][0].size());PAR1 = DA[Y][u];
			//vector<int> PAR2(CA[0][0].size());PAR2 = CA[K][u];
			for (j = 0; j < CA[0][0].size(); ++j) {
				int par1 = DA[Y][u][j];
				int par2 = CA[K][u][j];
				double r2 = (double)rand() / RAND_MAX;
				if (r2 <= 0.5) {
					y1 = min(par1, par2), y2 = max(par1, par2);
					if ((y1 - yd) > (yu - y2)) {
						beta = 1.0 + 2 * (yu - y2) / (y2 - y1);
					}
					else {
						beta = 1.0 + 2 * (y1 - yd) / (y2 - y1);
					}
					expp = eta_c + 1.0; beta = 1.0 / beta; alpha = 2.0 - pow(beta, expp);
					double r3 = (double)rand() / RAND_MAX;
					if (r3 <= 1.0 / alpha) {
						alpha = alpha*r3;
						expp = 1.0 / (eta_c + 1.0);
						betaq = pow(alpha, expp);
					}
					else {
						alpha = 1.0 / (2.0 - alpha*r3);
						expp = 1.0 / (eta_c + 1.0);
						betaq = pow(alpha, expp);
					}
					chld1 = 0.5*((y1 + y2) - betaq*(y2 - y1));
					chld2 = 0.5*((y1 + y2) + betaq*(y2 - y1));
					aa = max(chld1, yd);
					bb = max(chld2, yd);
					aa = min(aa, yu);
					bb = min(bb, yu);
					if (notFiniteNumber1(aa)|| notFiniteNumber1(bb)) {
						npop[2 * i][u][j] = par1; npop[2 * i + 1][u][j] = par2;
					}
					else {
						if (cyu[2 * i][Round(aa)] == 1) {
							npop[2 * i][u][j] = Round(aa);
						}
						else {
							npop[2 * i][u][j] = par1;
						}
						if (cyu[2 * i + 1][Round(bb)] == 1) {
							npop[2 * i + 1][u][j] = Round(bb);
						}
						else {
							npop[2 * i + 1][u][j] = par2;
						}
					}
				}//r2
				else {
					npop[2 * i][u][j] = par1;
					npop[2 * i + 1][u][j] = par2;
				}
			}
		}
		if (!Constraint(npop[2 * i], cyu[2 * i], buv, cu, cuv, nuv)) {
			npop[2 * i] = DA[Y];
			cyu[2 * i] = DAYU[Y];
		}
		if (!Constraint(npop[2 * i+1], cyu[2 * i+1], buv, cu, cuv, nuv)) {
			npop[2 * i+1] = CA[K];
			cyu[2 * i+1] = CAYU[K];
		}
	}//loop i
	return npop;
}