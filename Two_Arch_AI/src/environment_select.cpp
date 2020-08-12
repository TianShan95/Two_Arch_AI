#include"Init.h"


int es(vector<vector<vector<vector<double>>>> &P, vector<double>&F, vector<vector<double> >&Pobj)
{
	int N = 100;
	int i, j, k;
	int m = Pobj[0].size();
	int n = P.size();
	vector<vector<double > > cobj(Pobj);
	double *big = new double[m], *small = new double[m];
	double **imax = new double*[n];
	for (i = 0; i < n; i++)
	{
		imax[i] = new double[m];
	}
	for (i = 0; i < m; i++)
	{
		big[i] = -INT_MAX;
		small[i] = INT_MAX;
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
	vector<double> C(n);
	vector<double> t2(n);
	for (i = 0; i < n; i++)
	{
		C[i] = 0.0;
		vector<vector<double > > t(cobj);
		t.erase(t.begin() + i);
		for (k = 0; k < n - 1; k++)
		{
			for (j = 0; j < m; j++)
			{
				imax[k][j] = t[k][j] - cobj[i][j];
			}
		}
		for (k = 0; k < n - 1; k++)
		{
			t2[k] = -9999;
			for (j = 0; j < m; j++)
			{
				t2[k] = max(t2[k], imax[k][j]);
			}
		}
		for (k = 0; k < n - 1; k++)
		{
			C[i] = max(C[i], fabs(t2[k]));
		}
	}
	int E;
	while (P.size() > N)
	{
		auto e = min_element(F.begin(), F.end());
		E = e - F.begin();
		double *t3 = new double[m];
		for (i = 0; i < m; i++)
		{
			t3[i] = cobj[E][i];
		}
		cobj.erase(cobj.begin() + E);
		for (i = 0; i < cobj.size(); i++)
		{
			t2[i] = -9999.0;
			for (j = 0; j < m; j++)
			{
				t2[i] = max(t2[i], (t3[j] - cobj[i][j]));
			}
		}
		P.erase(P.begin() + E);
		Pobj.erase(Pobj.begin() + E);
		F.erase(F.begin() + E);
		for (k = 0; k < P.size(); k++)
		{
			F[k] = F[k] + exp(0 - t2[k] / (C[E] * 0.05));
		}
		C.erase(C.begin() + E);
	}
	return 1;
}