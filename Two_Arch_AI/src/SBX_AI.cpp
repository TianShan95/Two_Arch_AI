#include"Init.h"


int Round(double num) {
	return num > 0.0 ? (num + 0.5) : (num - 0.5);
}
int notFiniteNumber1(double d)  // ����������1��������Ϊ�����ĸ���������0������0
{
	switch (fpclassify(d)) {
	case FP_INFINITE:  return 1;  // d���������� 
	case FP_NAN:       return 1;  // d����һ����
	case FP_ZERO:      return 0;  // dΪ0
	case FP_SUBNORMAL: return 1;  // d̫С�����ڲ����ø������Ĺ����ʽ��ʾ
	case FP_NORMAL:	   return 0;  // Ϊ�����ĸ�����
	}
}

/*
*SBX:ģ������ƽ��棨Simulated binary crossover),��Ҫ���ѡ����������
*���Ӧ���ǽ���������cpopҲ���ǽ����Ӵ����Ǵ��������������
*/
vector<vector<vector<vector<double>>>> SBXAI(vector<vector<vector<vector<double>>>>&CA, \
	vector<vector<vector<vector<double>>>>&DA, vector<vector<double>>&CAobj, \
	   vector<vector<double> >&DAobj, int n, int m, double* Num_Of_Core_Per_ES)
{
	int i, j;
	vector<vector<vector<vector <double>>>> npop(2 * n);  // ����һ��4ά����npop(continue population)�������������Ľ⼯
	vector<vector<vector<vector <double>>>> ES_Mark(2 * n);  // ���������ż���������Ǹ���
	
	for (i = 0; i < 2 * n; i += 1)   // ��npop����ռ�
	{
		ES_Mark[i].resize(CA[0].size());
		npop[i].resize(CA[0].size());
		for (j = 0; j < CA[0].size(); ++j) {
			npop[i][j].resize(CA[0][0].size());  // npop[][]���Է��ʵ��ڼ���
		}
	}
	int lenDA = DA.size();  // ����lenDA�����DA�����Դ浵����Ⱥ����
	int K, Y;
	double eta_c = 15.0; double yd, yu, expp, y1, y2;
	double beta, alpha, betaq, chld1, chld2, aa, bb;
	vector<double> do1(m), do2(m);
	srand((unsigned)time(0));
	for (i = 0; i < n; i++)  // ��ѯCA�ĵ�n����Ⱥ---------------------------------------------------------first for
	{
		int k1 = rand() % CA.size();
		int k2 = rand() % CA.size();
		while (k1 == k2) { k2 = rand() % CA.size(); }  // ����������ͬ���������CA��pop����Ⱥ
		/***���ѡ�����ν�����Ŀ���������ֱ�����Ϊdo1��do2**/
		do1 = CAobj[k1];
		do2 = CAobj[k2];
		int z = dom(do1, do2, m);  // ������ص�z��ʾ��do1��do2�����ν������Ŀ��ֵ�ĶԱȽ��

		/* do1�ֵ�Ŀ��ֵȫ��С��do2�ֵ�Ŀ��ֵ,Ҳ�����±�Ϊk1��Ŀ������ֵȫ����ѹ�±�Ϊk2��Ŀ��ֵ��Kȡ������±�
		*�����������Ŀ��ֵȫ����ѹ��������ķ�ʽȷ��K��ȡk1����k2
		*/
		if (z == 1) { K = k1; }  
		else if (z == 2) { K = k2; }
		else if (((double)rand() / RAND_MAX) <= 0.5) { K = k1; }
		else { K = k2; }
		Y = rand() % lenDA;  // ����һ���������Ϊ������forѭ�����ѡ����Ⱥ�õ�

		for (int u = 0; u < CA[0].size(); ++u)   // ��ѯCA��ÿ����Ⱥ��ÿ����------------------------------second for
		{
			yd = 0; // �½�
			yu = 1; // �Ͻ�

			//vector<int> PAR1(DA[0][0].size());PAR1 = DA[Y][u];
			//vector<int> PAR2(CA[0][0].size());PAR2 = CA[K][u];
			for (j = 0; j < CA[0][0].size(); ++j) // ��ѯCAÿ����Ⱥ��ÿ�����ÿ������-------------------------third for
			{
				/**ȡ�������������Ⱥ��ȡ��������Ⱥ��Ӧ��Ķ�Ӧ�����ES��־λ**/
				int par1 = DA[Y][u][j][2];  
				int par2 = CA[K][u][j][2];

				double r2 = (double)rand() / RAND_MAX;  //����һ��0-1֮��������

				if (r2 <= 0.5)  // ���Ǳ�ʾ��һ��ĸ��ʻᷢ��if��ı仯
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

					if (notFiniteNumber1(aa)) {  // ���aa��������������ĸ���ѡ��aa��0����1
						if ((double)rand() / RAND_MAX <= 0.5) { aa = yu; }
						else { aa = yd; }
					}
					if (notFiniteNumber1(bb)) {  // ���bb��������������ĸ���ѡ��aa��0����1
						if ((double)rand() / RAND_MAX <= 0.5){bb = yu;}
						else { bb = yd; }
					}
					ES_Mark[2 * i][u][j][2] = Round(aa);  // ��aa��bb��ֵ�浽ES_Mark��
					ES_Mark[2 * i + 1][u][j][2] = Round(bb);
				}
				else {
					ES_Mark[2 * i][u][j][2] = par1;
					ES_Mark[2 * i + 1][u][j][2] = par2;
				}
			}  // loop j
		}  // loop u
		if (!Constraint(npop[2 * i], Num_Of_Core_Per_ES))   // �������ⲻ��������
		{
			npop[2 * i] = DA[Y];
			ES_Mark[2 * i] = CA[Y];
		}
		if (!Constraint(npop[2 * i + 1], Num_Of_Core_Per_ES))   // �������ⲻ�������ƣ��Ͱ�ԭ�����ȡ�÷Ž�ȥ
		{
			npop[2 * i + 1] = DA[K];
			ES_Mark[2 * i + 1] = CA[K];
		}
	}  // loop i
	return npop;
}