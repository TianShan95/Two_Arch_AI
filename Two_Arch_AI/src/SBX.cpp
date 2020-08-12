#include"Init.h"


double **SBX(vector<vector<double > >pop, double **Boundary, int n, int c, int m)
{
	int i, j;
	vector< vector <double  > > npop(2 * n);
	//vector< vector <double  > > NPOP(2 * n);
	//vector< vector <double  > > obj;
	double **obj;
	double **NPOP = new double*[2 * n];
	for (i = 0; i < 2 * n; i += 1)
	{
		NPOP[i] = new double[c + m];
		npop[i].resize(c);
	}
	int eta_c = 15;
	double yy1, yy2, beta, expp, alpha;
	srand((unsigned)time(NULL));
	for (i = 0; i < n; i += 1)
	{
		double r1 = (double)rand() / RAND_MAX;
		if (r1 <= 1)
		{
			int x1 = rand() % n;//生成2个1~n的随机数
			int x2 = rand() % n;
			if (x1 == x2)
			{
				do {
					x2 = rand() % n;
				} while (x1 != x2);
			}
			for (j = 0; j < c; j += 1)
			{
				double par1 = pop[x2][j];
				double par2 = pop[x1][j];
				double betaq;
				double chld1, chld2, aa, bb;
				double yd = Boundary[1][j];
				double yu = Boundary[0][j];
				double r2 = (double)rand() / RAND_MAX;
				if (r2 <= 0.5)
				{
					yy1 = min(par1, par2); yy2 = max(par1, par2);
					if ((yy1 - yd) > (yu - yy2))
					{
						beta = 1 + 2 * (yu - yy2) / (yy2 - yy1);
					}
					else
					{
						beta = 1 + 2 * (yy1 - yd) / (yy2 - yy1);
					}
					expp = eta_c + 1; beta = 1.0 / beta; alpha = 2.0 - pow(beta, expp);
					double r3 = (double)rand() / RAND_MAX;
					if (r3 < 1 / alpha)
					{
						alpha = alpha * r3; expp = 1.0 / (eta_c + 1.0);
						betaq = pow(alpha, expp);
					}
					else
					{
						alpha = 1.0 / (2.0 - alpha * r3); expp = 1.0 / (eta_c + 1);
						betaq = pow(alpha, expp);
					}
					chld1 = 0.5*((yy1 + yy2) - betaq * (yy2 - yy1));
					chld2 = 0.5*((yy1 + yy2) + betaq * (yy2 - yy1));
					aa = max(chld1, Boundary[1][j]);
					bb = max(chld2, Boundary[1][j]);
					double r4 = (double)rand() / RAND_MAX;
					if (r4 > 0.5)
					{
						npop[2 * i][j] = min(aa, Boundary[0][j]);
						npop[2 * i + 1][j] = min(bb, Boundary[0][j]);
					}
					else
					{
						npop[2 * i + 1][j] = min(aa, Boundary[0][j]);
						npop[2 * i][j] = min(bb, Boundary[0][j]);
					}
				}
				else
				{
					npop[2 * i][j] = par1;
					npop[2 * i + 1][j] = par2;
				}
			}
		}
	}
	obj = com_obj(npop, m);
	for (i = 0; i < 2 * n; i += 1)
	{
		for (j = 0; j < c; j += 1)
		{
			NPOP[i][j] = npop[i][j];
		}
		for (j = c; j < c + m; j += 1)
		{
			NPOP[i][j] = obj[i][j - c];
		}
	}
	//cout << "ss" << endl;
	return NPOP;
}