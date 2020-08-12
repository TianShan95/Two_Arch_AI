#include"Init.h"



int updateDA(vector<vector<vector<vector<double>>>>&CPOP, \
			 vector<vector<vector<vector<double>>>>&DA,\
			 vector<vector<double> >&cobj, vector<vector<double> >&DAobj)
{
	int nc = CPOP.size();
	int i, j, k, n = 100;
	int flag, u;
	int lenDA = DA.size();
	int m = DAobj[0].size();  // m��Ŀ����
	vector<int> PP;
	//double *x1 = new double[c + m], *x2 = new double[c + m];
	for (i = 0; i < CPOP.size(); i++)
	{
		flag = 0;
		vector<double > x1(m);
		vector<double > x2(m);
		j = 0;
		while (j < lenDA)  // ��ѯDA�����Ⱥ
		{
			x1 = cobj[i];  // ��while��̶�סĳһ�ֵ�x1
			x2 = DAobj[j];
			u = dom(x1, x2, m);  // �Ա��ĸ�Ŀ��ֵ����
			if (u == 2)  // x1��i���ֵ�Ŀ��ֵȫ������x2�ֵ�Ŀ��ֵ����x2��j����Ŀ��ֵȫ������x1��i�����������Ż�ʹ����Ŀ��ֵ��С
			{
				flag = 1;
				break;
			}
			else if (u == 1)  // x1(i)�ֵ�Ŀ��ֵȫ��С��x2�ֵ�Ŀ��ֵ����x1(i)��Ŀ��ֵȫ������x2���������Ż�ʹ����Ŀ��ֵ��С
			{
				DA.erase(DA.begin() + j);
				DAobj.erase(DAobj.begin() + j);  // ��x2��Ŀ��ֵȫ��������j��Ӧx2

				lenDA--;//��Ϊ������һ�������Գ�������һ��
			}
			else if (u == 3)  // ����ǧ�x1��������x2��Ŀ��ֵ��x2��Ҳ������x1��Ŀ��ֵ
			{
				flag = 1;
				break;
			}
			else
			{
				j++;  // ����һ�����������ά������x2
			}
		}
		if (flag == 0)  // �����x1(i)�������ŵ�
		{
			PP.push_back(i);  // �����ŵ��Ǹ�i����PP
		}
	}
	int PP_size = PP.size();  //�����ŵ�������PP_size

	vector<vector<vector<vector<double>>>>NDA(lenDA + PP_size);  // �����������������ŵĸ���i+j
	vector<vector<double>>NDAobj(lenDA + PP_size);

	for (i = 0; i < lenDA + PP_size; i++)  // ��ѯ���е����ţ������е����ŵ���Ⱥ�浽NDA����Ӧ������Ŀ��ֵ�浽NDAobj
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
	if (lenDA > n)  // ����õ��Ľ�������õ���Ⱥ���������󣬾ͽ���һ��select
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
	LL = NDA.size();  // ���ŵ���Ⱥ����LL
	int m = NDAobj[0].size();  // m��Ŀ������
	vector<int>a(2 * m);  // ����һ������������������Ŀ��ֵ�����Ǹ����������Ŀ��ֵ��С���Ǹ��������
	DA.clear(), DAobj.clear();   //  �Ȱ��������������
	for (i = 0; i < m; i++)  // ��ѯÿ��Ŀ��ֵ
	{
		a[i] = 0;
		for (j = 1; j < LL; j++)  //�̶�סi����Ӧ��ͬ�ֽ�����ͬһĿ��ֵ�Ա�
		{
			if (NDAobj[j][i] < NDAobj[a[i]][i])  // ���j�ֵ�Ŀ��ֵ��С����j�ֱ��ָ����㣬����������������a
			{
				a[i] = j;  // �������СĿ��ֵ�ķ���
			}
		}
		a[m + i] = 0;
		for (j = 1; j < LL; j++)
		{
			if (NDAobj[j][i] > NDAobj[a[m + i]][i])
			{
				a[m + i] = j;  // ��������Ŀ��ֵ�ķ���
			}
		}
	}
	sort(a.begin(), a.end());  // �ѽ��������С��������
	a.erase(unique(a.begin(), a.end()), a.end());  // ���ظ���ȥ��������
	for (i = 0; i < a.size(); i++)  // ��������С���ȴ���DA��
	{
		DA.push_back(NDA[a[i]]);
		DAobj.push_back(NDAobj[a[i]]);
	}
	for (i = 0; i < a.size(); i++)//��Ǵ��Ǹ������С���ļ����������
	{
		NDA[a[i]][0][0][2] = -1;
	}
	for (i = 0; i < NDA.size(); i++)
	{
		if (NDA[i][0][0][2] == -1)  // �Ѵ���Ǽ�����NDA��ɾ��
		{
			NDA.erase(NDA.begin() + i);
			NDAobj.erase(NDAobj.begin() + i);

			--i;
		}
	}
	int N = a.size();   //NDA����
	double W[800][20];
	double dis[800];
	double d[800];
	int t = 0; int K; double din[800];
	int iq, ip; double sum;
	double lp = 1.0 / m;
	while (NDA.size() > 0 && DA.size() < 100)
	{
		for (i = 0; i < NDA.size(); i += 1)  //Ҫ�ѽ������һ������NDA
		{
			d[i] = INT_MAX;
			for (iq = 0; iq < N; iq += 1)
			{
				sum = 0;
				for (j = 0; j < m; j += 1)
				{
					sum += pow((fabs(DAobj[iq][j] - NDAobj[i][j])), lp);
				}
				d[i] = min(d[i], pow(sum, m));  // ȡ������С�ľ���Ž�d[i]
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