/*
 1.ifs���ļ�
 2.������ָ����vector
 3.β��
*/
#include"Read_Load_Rate.h"
#include<iomanip>


void Read_Load_Rate(vector<vector<vector<double>>> &p)
{
	ifstream ifs;
	ifs.open("D:/temp/Load_Rate_To_Program_01.txt");
	string s;
	auto fit = p.begin();
	auto sit = (*fit).begin();
	double a;
	while(getline(ifs ,s))
	{
		istringstream iss(s);
		iss >> a;
		//cout << "-----------" << endl;
		//cout << "a: " <<fixed<<setprecision(10)<< a << " s: " << s << endl;
		//cout << "-----------" << endl;
		if (sit == (*fit).end())  // �ж��Ƿ����һ��
		{
			fit++;
			if (fit == p.end())
				break;
			sit = (*fit).begin();
		}
		(*sit).push_back(a);   // β�帺����
		sit++;
	}
	ifs.close();
}