#include"Init.h"


vector<double> fitness(vector<vector<double> >&Pobj)
{
	int n = Pobj.size();
	int i, j, k;
	int m = Pobj[0].size();
	vector<vector<double > > cobj(Pobj), imax(n);
	vector<double> big(m), small(m);
	for (i = 0; i < n; i++)
	{
		imax[i].resize(m);
	}
	for (i = 0; i < m; i++)
	{
		big[i] = 0;
		small[i] = 10000;
	}
	for (j = 0; j < m; j++)
	{
		for (i = 0; i < n; i++)
		{
			big[j] = max(big[j], cobj[i][j]);
			small[j] = min(small[j], cobj[i][j]);
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cobj[i][j] = (cobj[i][j] - small[j]) / (big[j] - small[j]);
		}
	}
	vector<double> F;
	F.resize(n);
	double *t2 = new double[n];
	for (i = 0; i < n; i++)
	{
		F[i] = 0.0;
		for (j = 0; j < n; j++)
		{
			if (j != i)
			{
				t2[j] = -99999.0;
				for (k = 0; k < m; k++)
				{
					t2[j] = max((cobj[j][k] - cobj[i][k]), t2[j]);
				}
			}
		}
		double A;
		A = -INT_MAX;
		for (j = 0; j < n; j++)
		{
			if (j != i)
			{
				A = max(A, fabs(t2[j]));
			}
		}
		for (j = 0; j < n; j++)
		{
			if (j != i)
			{
				F[i] = F[i] - exp((0.0 - t2[j] / (A*0.05)));


			}
		}
	}
	return F;
}