#include"Init.h"


double **mutation(vector<vector <double> > x, double **Boundary, int n, int c, int m, double pm)//len记录x的行数
{
	int i, j, k; double eta_m = 15.0;
	double y, yu, yd, indi, delta, xy, val, deltaq;
	int len = x.size();
	vector<vector<double > >NPOP(n);
	//vector<vector<double > >npop(n);
	//vector<vector<double > >obj;
	double **obj;
	double **npop = new double*[n];
	for (i = 0; i < n; i += 1)
	{
		NPOP[i].resize(c);
		npop[i] = new double[c + m];
	}
	for (i = 0; i < len; i += 1)
	{
		for (j = 0; j < c; j++)
		{
			NPOP[i][j] = x[i][j];
		}
	}
	srand((unsigned)time(NULL));
	for (i = 0; i < n; i += 1)
	{
		k = (int)rand() % len;
		for (j = 0; j < c; j++)
		{
			NPOP[i][j] = x[k][j];
		}
		for (j = 0; j < c; j += 1)
		{
			double r1 = (double)rand() / RAND_MAX;
			if (r1 <= pm)
			{
				y = x[k][j];
				yu = Boundary[0][j];
				yd = Boundary[1][j];
				if (y > yd)
				{
					if ((y - yd) < (yu - y))
					{
						delta = (y - yd) / (yu - yd);
					}
					else
					{
						delta = (yu - y) / (yu - yd);
					}
					indi = 1.0 / (eta_m + 1);
					double(r2) = (double)rand() / RAND_MAX;
					if ((r2) <= 0.5)
					{
						xy = 1.0 - delta;
						val = 2.0*r2 + (1.0 - 2 * r2)*pow(xy, (eta_m + 1.0));
						//cout<<val<<endl;
						deltaq = pow(val, indi) - 1.0;
						//	cout<<deltaq;
					}
					else
					{
						xy = 1.0 - delta;
						val = 2.0*(1.0 - (r2)) + 2.0*((r2)-0.5)*pow(xy, (eta_m + 1.0));
						deltaq = 1.0 - pow(val, indi);
						//	cout<<deltaq;
					}
					//cout<<deltaq<<"  ";
					y += deltaq * (yu - yd);
					y = max(y, yd);
					y = min(y, yu);
					//			cout<<y<<endl;
					NPOP[i][j] = y;
				}
				else
				{
					NPOP[i][j] = ((double)rand() / RAND_MAX)*(yu - yd) + yd;
				}

			}//r1
		}
	}//i xunhuan
	obj = com_obj(NPOP, m);
	for (i = 0; i < n; i += 1)
	{
		for (j = 0; j < c; j += 1)
		{
			npop[i][j] = NPOP[i][j];
		}
		for (j = c; j < c + m; j += 1)
		{
			npop[i][j] = obj[i][j - c];
		}
	}
	return npop;
}