#include"Init.h"


double **com_obj(vector<vector<double>>x, int m)
/*{//dtlz1
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	//vector<vector<double > >obj(n);
	double **obj=new double*[n];
	int i, j, k;
	vector<double>g(n);
	for (i = 0;i<n;i++)
	{
		obj[i]=new double[m];
		g[i] = 0;
		for (j = (m - 1);j<c;j++)
		{
			g[i] += (pow((x[i][j] - 0.5), 2.0) - cos(20 * M_PI*(x[i][j] - 0.5)));
		}
		g[i] = 100 * (g[i] + (c - m + 1));
	}
	vector<double>prod(n);
	for (i = 0;i<n;i++)
	{
		prod[i] = 1.0;
		for (j = 0;j<(m - 1);j++)
		{
			prod[i] = prod[i] * x[i][j];
		}
		obj[i][0] = prod[i] * (1 + g[i]);
	}
	for (i = 0;i<n;i++)
	{
		for (j = 1;j<m - 1;j++)
		{
			prod[i] = 1.0;
			for (k = 0;k<m - j - 1;k++)
			{
				prod[i] = prod[i] * x[i][k];
			}
			obj[i][j] = prod[i] * (1 - x[i][m - j - 1])*(1 + g[i]);
		}
		obj[i][m - 1] = (1 - x[i][0])*(1 + g[i]);
	}
	return obj;
}*/
/*void dtlz1(double *xreal, double *obj, int dim, int EMO_nobj)
{
	double sum = 0;
	double gx;
	int i, j;

	for (i = EMO_nobj - 1; i < dim; i++) {
		sum += pow((xreal[i] - 0.5), 2.0) - cos(20 * M_PI * (xreal[i] - 0.5));
	}

	gx = 100 * (sum + dim - EMO_nobj + 1) + 1.0;
	sum = gx;

	for (j = 0; j < EMO_nobj - 1; j++) {
		sum = sum * xreal[j];
	}

	obj[0] = 0.5 * sum;

	for (i = 1; i < EMO_nobj; i++) {
		sum = gx;

		for (j = 0; j < EMO_nobj - 1 - i; j++) {
			sum = sum * xreal[j];
		}

		sum = sum * (1.0 - xreal[EMO_nobj - 1 - i]);
		obj[i] = 0.5 * sum;
	}

	return;
}*/

//dtlz2
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	//vector<vector<double > >obj(n);
	double **obj = new double*[n];
	vector<double>g(n), prod(n);
	for (i = 0; i < n; i += 1)
	{
		obj[i] = new double[m];
		g[i] = 0;
		for (j = m - 1; j < c; j++)
		{
			g[i] += pow((x[i][j] - 0.5), 2);
		}
	}
	for (i = 0; i < n; i += 1)
	{
		prod[i] = 1.0;
		for (j = 0; j < m - 1; j++)
		{
			prod[i] = prod[i] * cos(0.5*M_PI*x[i][j]);
		}
		obj[i][0] = prod[i] * (1 + g[i]);
	}
	for (i = 0; i < n; i += 1)
	{
		for (j = 1; j < m - 1; j += 1)
		{
			prod[i] = 1.0;
			for (k = 0; k < m - j - 1; k++)
			{
				prod[i] = prod[i] * cos(0.5*M_PI*x[i][k]);
			}
			obj[i][j] = prod[i] * sin(0.5*M_PI*x[i][m - j - 1])*(1 + g[i]);
		}
		obj[i][m - 1] = sin(0.5*M_PI*x[i][0])*(1 + g[i]);
	}
	return obj;
}

/*//dtlz3
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n), prod(n);
	for (i = 0;i<n;i++)
	{
		obj[i].resize(m);
		g[i] = 0;
		for (j = (m - 1);j<c;j++)
		{
			g[i] += (pow((x[i][j] - 0.5), 2) - cos(20 * M_PI*(x[i][j] - 0.5)));
		}
		g[i] = 100 * (g[i] + (c - m + 1));
	}
	for (i = 0;i<n;i++)
	{
		prod[i] = 1.0;
		for (j = 0;j<(m - 1);j++)
		{
			prod[i] = prod[i] * cos(0.5*M_PI*x[i][j]);
		}
		obj[i][0] = prod[i] * (1 + g[i]);
	}
	for (i = 0;i<n;i++)
	{
		for (j = 1;j<m - 1;j++)
		{
			prod[i] = 1.0;
			for (k = 0;k<m - j - 1;k++)
			{
				prod[i] = prod[i] * cos(0.5*M_PI*x[i][k]);
			}
			obj[i][j] = prod[i] * sin(0.5*M_PI*x[i][m - j - 1])*(1 + g[i]);
		}
		obj[i][m - 1] = sin(0.5*M_PI*x[i][0])*(1 + g[i]);
	}
	return obj;
}*/



/*//dtlz4
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n), prod(n);
	for (i = 0;i<n;i++)
	{
		obj[i].resize(m);
		g[i] = 0;
		for (j = (m - 1);j<c;j++)
		{
			g[i] += (pow((x[i][j] - 0.5), 2));
		}
	}
	for (i = 0;i<n;i++)
	{
		prod[i] = 1.0;
		for (j = 0;j<(m - 1);j++)
		{
			prod[i] = prod[i] * cos(0.5*M_PI*pow(x[i][j], 100));
		}
		obj[i][0] = prod[i] * (1 + g[i]);
	}
	for (i = 0;i<n;i++)
	{
		for (j = 1;j<m - 1;j++)
		{
			prod[i] = 1.0;
			for (k = 0;k<m - j - 1;k++)
			{
				prod[i] = prod[i] * cos(0.5*M_PI*pow(x[i][j], 100));
			}
			obj[i][j] = prod[i] * sin(0.5*M_PI*pow(x[i][m - j - 1], 100))*(1 + g[i]);
		}
		obj[i][m - 1] = sin(0.5*M_PI*pow(x[i][0], 100))*(1 + g[i]);
	}
	return obj;
}*/

/*//dtlz5
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n), prod(n);
	for (i = 0; i<n; i++)
	{
		obj[i].resize(m);
		g[i] = 0;
		for (j = (m - 1); j<c; j++)
		{
			g[i] += (pow((x[i][j] - 0.5), 2));
		}
		obj[i][m - 1] = (1 + g[i])*sin(0.5*M_PI*x[i][0]);
		for (j = 0; j < m - 1; j++)
		{
			obj[i][j] = (1 + g[i])*cos(0.5*M_PI*x[i][0]);

		}for (j = 1; j < m - 1; j++)
		{
			obj[i][0] *= cos((0.25*M_PI / (1 + g[i]))*(1 + 2 * g[i] * x[i][j]));
		}
		for (j = 1; j<m - 1; j++) {
			for (k = 1; k<m - j - 1; k++) {
				obj[i][j] *= cos((0.25*M_PI / (1 + g[i]))*(1 + 2 * g[i]*x[i][k]));
			}
			obj[i][j] *= sin((0.25*M_PI / (1 + g[i]))*(1 + 2 * g[i]*x[i][k]));
		}
	}
	return obj;
}*/

/*//dtlz6
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n), prod(n);
	for (i = 0; i<n; i++)
	{
		obj[i].resize(m);
		g[i] = 0;
		for (j = m - 1; j < c; j++)
		{
			if(x[i][j]<0.25)
			{
				x[i][j] = 0;
			}
			g[i] += pow(x[i][j], 0.1);
		}
		obj[i][m - 1] = (1 + g[i])*sin(0.5*M_PI*x[i][0]);
		for (j = 0; j < m - 1; j++)
		{
			obj[i][j] = (1 + g[i])*cos(0.5*M_PI*x[i][0]);
		}
		for (j = 1; j < m - 1; j++)
		{
			obj[i][0] *= cos((0.25*M_PI / (1 + g[i]))*(1 + 2 * g[i]*x[i][j]));
		}
		for (j = 1; j<m - 1; j++) {
			for (k = 1; k<m - j - 1; k++) {
				obj[i][j] *= cos((0.25*M_PI / (1 + g[i]))*(1 + 2 * g[i]*x[i][k]));
			}
			obj[i][j] *= sin((0.25*M_PI / (1 + g[i]))*(1 + 2 * g[i]*x[i][k]));
		}
	}
	return obj;
}*/

/*//dtlz7
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n), prod(n),h(n);
	for (i = 0; i < n; i++)
	{
		g[i] = 0;
		h[i] = 0;
		obj[i].resize(m);
		for (j = 0; j < m - 1; j++)
		{
			obj[i][j] = x[i][j];
		}
		for (j = m - 1; j < c; j++)
			g[i] += x[i][j];
		g[i] = 1 + (9.0 / (c-m+1))*g[i];
		for (j = 0; j<m - 1; j++)
			h[i] += (obj[i][j] / (1 + g[i]))*(1 + sin(3 * M_PI*obj[i][j]));
		h[i] = m - h[i];
		obj[i][m - 1] = (1 + g[i])*h[i];
	}
	return obj;
}*/







/*//ZDT1
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n);
	for (i = 0;i<n;i++)
	{
		obj[i].resize(m);
		obj[i][0] = x[i][0];
		g[i] = 0;
		for (j = 1;j<c;j++)
		{
			g[i] += x[i][j];
		}
		g[i] = g[i] / (c - 1) * 9;
		g[i] = g[i] + 1;
		obj[i][1] = g[i] * (1 - pow(x[i][0] / g[i]), 0.5);
	}
	return obj;
}*/

/*//ZDT2
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n);
	for (i = 0;i<n;i++)
	{
		obj[i].resize(m);
		obj[i][0] = x[i][0];
		g[i] = 0;
		for (j = 1;j<c;j++)
		{
			g[i] += x[i][j];
		}
		g[i] = g[i] / (c - 1) * 9;
		g[i] = g[i] + 1;
		obj[i][1] = g[i] * (1 - pow(x[i][0] / g[i]), 2);
	}
	return obj;

}*/

/*// ZDT3
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n);
	for (i = 0;i<n;i++)
	{
		obj[i].resize(m);
		obj[i][0] = x[i][0];
		g[i] = 0;
		for (j = 1;j<c;j++)
		{
			g[i] += x[i][j];
		}
		g[i] = g[i] / (c - 1);
		g[i] = g[i] + 1;
		obj[i][1] = g[i] * (1 - pow(x[i][0] / g[i]), 0.5 - (x[i][0] / g[i] * sin(10 * M_PI*x[i][0])));
	}
	return obj;
}*/

/*//ZDT4
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n);
	for (i = 0;i<n;i++)
	{
		obj[i].resize(m);
		obj[i][0] = x[i][0];
		g[i] = 0;
		for (j = 1;j<c;j++)
		{
			g[i] += pow(x[i][j], 2) - 10 * cos(4 * M_PI*x[i][j]);
		}
		g[i] = g[i] + 1 + (c - 1) * 10;
		obj[i][1] = g[i] * (1 - pow(x[i][0] / g[i], 0.5));
	}
	return obj;
}*/

/*//ZDT6
{
	int n = x.size();//x Ϊpop
	int c = x[0].size();
	int i, j, k;
	vector<vector<double > >obj(n);
	vector<double>g(n);
	for (i = 0;i<n;i++)
	{
		obj[i].resize(m);
		obj[i][0] = 1 - pow(exp, -4 * x[i][0])*pow(sin(6 * M_PI*x[i][0]), 6);
		g[i] = 0;
		for (j = 1;j<c;j++)
		{
			g[i] += pow(x[i][j], 2) - 10 * cos(4 * M_PI*x[i][j]);
		}
		g[i] = g[i] + 1 + (c - 1) * 10;
		obj[i][1] = g[i] * (1 - pow(x[i][0] / g[i], 0.5));
	}
	return obj;
}*/


