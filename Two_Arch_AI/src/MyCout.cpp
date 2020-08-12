#include"MyCout.h"

void MyPrint_3_Dimension_Vector(vector<vector<vector<double>>> Three_Dimension_Vector)
{
	int i = 0;
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		cout << ++i << endl;
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)
		{
			for (vector<double> ::iterator t = (*itt).begin(); t != (*itt).end(); t++)
			{
				cout << (*t) << " ";


			}cout << endl;
		}
	}
}