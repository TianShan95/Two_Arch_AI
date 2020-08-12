#include"Init.h"

vector<vector<vector<vector<double>>>> updateCA(vector<vector<vector<vector<double>>>>&NPOP, \
												vector<vector<vector<vector<double>>>>&CA, \
												vector<vector<double>>&nobj, vector<vector<double>>&obj)
{
	int i, j, k, z;
	vector<vector<vector<vector<double>>>> P;  // 这个P就是为了把NPOP和CA合并
	vector<vector<double> >Pobj;  // 为了把nobj和obj合并

	/**********把NPOP和CA合并到P********/
	P.insert(P.end(), NPOP.begin(), NPOP.end());
	P.insert(P.end(), CA.begin(), CA.end());
	/**********把nobj和obj合并到Pobj********/
	Pobj.insert(Pobj.end(), nobj.begin(), nobj.end());
	Pobj.insert(Pobj.end(), obj.begin(), obj.end());

	/*删除P中的相同解*/
	i = 0;
	int m = Pobj[0].size();
	vector<double> a(m), b(m);
	while (i < P.size()) {  // 把所有目标值相同的都擦除
		j = i + 1;
		a = Pobj[i];
		while (j < P.size()) {
			b = Pobj[j];
			z = dom(a, b, m);  //比较a轮和b轮目标值的优劣
			if (z == 3) {   // 如果a轮和b轮目标值相同就擦除一个
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