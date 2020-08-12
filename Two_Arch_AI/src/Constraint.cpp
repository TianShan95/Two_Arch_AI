#include"Init.h"


bool Constraint(vector<vector<vector<double> > >&All_Position, double* Num_Of_Core_Per_ES) //Num_Of_Core_Per_ES是指向所有节点的核数，RSU的核数为0
{

	for (int i = 0; i < Node_Num; i++)
	{
		if (Num_Of_Core_Per_ES[i] > ES_Core_Max)
		{
			return false;
		}
		return true;
	} //判断是否超过边缘服务器的最大限度


	double temp1;
	double temp2;
	int q1 = 0;
	int q2 = 0;
	for (int i = 0; i < All_Position.size(); i++)
	{
		for (int j = 0; j < All_Position[i].size(); j++)
		{
			temp1 = All_Position[i][j][0];
			temp2 = All_Position[i][j][1];
			for (int i = 0; i < All_Position.size(); i++)
			{

				for (int j = 0; j < All_Position[i].size(); j++)
				{
					if ((All_Position[i][j][0] == temp1) && (All_Position[i][j][1] = temp2))
					{
						q1++;
					}

				}

			}
			if (q1 > 1) { return false; }
			else
			{
				return true;
			}
			q1 = 0;
		}

	}

	for (int i = 0; i < All_Position.size(); i++)
	{
		for (int j = 0; j < All_Position[i].size(); j++)
		{
			q1++;
			if (All_Position[i][j][2] = 1) {
				q2++;
			}
		}
	}

	if (q1 = Node_Num) { return true; }
	else { return false; }
	if (q2 = ES_Num) { return true; }
	else{return false;}


	
}