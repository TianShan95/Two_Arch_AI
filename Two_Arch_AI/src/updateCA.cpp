#include"Init.h"

vector<vector<vector<vector<double>>>> updateCA(vector<vector<vector<vector<double>>>>&NPOP, \
												vector<vector<vector<vector<double>>>>&CA, \
												vector<vector<double>>&nobj, vector<vector<double>>&obj)
{
	int i, j, k, z;
	vector<vector<vector<vector<double>>>> P;  // ���P����Ϊ�˰�NPOP��CA�ϲ�
	vector<vector<double> >Pobj;  // Ϊ�˰�nobj��obj�ϲ�

	/**********��NPOP��CA�ϲ���P********/
	P.insert(P.end(), NPOP.begin(), NPOP.end());
	P.insert(P.end(), CA.begin(), CA.end());
	/**********��nobj��obj�ϲ���Pobj********/
	Pobj.insert(Pobj.end(), nobj.begin(), nobj.end());
	Pobj.insert(Pobj.end(), obj.begin(), obj.end());

	/*ɾ��P�е���ͬ��*/
	i = 0;
	int m = Pobj[0].size();
	vector<double> a(m), b(m);
	while (i < P.size()) {  // ������Ŀ��ֵ��ͬ�Ķ�����
		j = i + 1;
		a = Pobj[i];
		while (j < P.size()) {
			b = Pobj[j];
			z = dom(a, b, m);  //�Ƚ�a�ֺ�b��Ŀ��ֵ������
			if (z == 3) {   // ���a�ֺ�b��Ŀ��ֵ��ͬ�Ͳ���һ��
				P.erase(P.begin() + j);
				Pobj.erase(Pobj.begin() + j);
			}
			else { j++; }
		}//j<p.size
		i++;
	}//i<p.size
	vector<double>F;
	F = fitness(Pobj);
	es(P, F, Pobj);
	//cout << P.size() <<"     "<<Pobj.size() <<"   "<<Pyn.size()<<endl;
	CA = P;

	obj = Pobj;
	return P;
}