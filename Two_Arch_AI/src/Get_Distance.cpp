#include"Get_Distance.h"

void Get_Distance(vector<vector<vector<double>>> &All_Position_0)
{
	double Store_Position[6];
	int ES_Flag = 0, Rank_0 = 0;  // i express which 
	for (vector<vector<vector<double>>>::iterator it = All_Position_0.begin(); it != All_Position_0.end(); it++)  //迭代每个类
	{

		//cout << Rank_0 << endl;  // 打印这是第几类
		if (Rank_0 == 38)
		{
			break;
		}
		int Rank_1 = 0;  // which Position
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // 迭代每个位置
		{
			int Rank_2 = 0;  // which attribute

			for (vector<double> ::iterator t = (*itt).begin(); t != (*itt).end(); t++)  // 迭代每个属性
			{

				Store_Position[Rank_2] = (*t);
				//cout << (*t) << " ";
				//cout << Store_Position[Rank_2] << " ";
				Rank_2++;
			}//cout << endl;
			if (Store_Position[2] == 1)
			{
				ES_Flag = Rank_1;
				//printf("______________________________");
			}

			Rank_1++;


			//printf("Rank_1:%d \n", Rank_1);

			//printf("PerCluster_Num:%d \n", PerCluster_Num[Rank_0]);
		}
		for (int h = 0; h < PerCluster_Num[Rank_0]; h++)
		{
			All_Position_0[Rank_0][h][3] = Caculate_Real_Distance(All_Position_0[Rank_0][ES_Flag], \
				All_Position_0[Rank_0][h]);
			//printf("hello");
			//cout << All_Position_0[Rank_0][h][3] << endl;
			All_Position_0[Rank_0][h][4] = Caculate_O_Distance(All_Position_0[Rank_0][ES_Flag],\
				All_Position_0[Rank_0][h]);


		}


		Rank_0++;

		///* 这是距离计算完时候的输出调试 */
		//int i = 0;
		//for (vector<vector<vector<double>>>::iterator it = All_Position_0.begin(); it != All_Position_0.end(); it++)
		//{
		//	cout << i << endl;
		//	for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)
		//	{
		//		for (vector<double> ::iterator t = (*itt).begin(); t != (*itt).end(); t++)
		//		{
		//			cout << (*t) << " ";


		//		}cout << endl;
		//	}
		//	All_Position_0[i].erase(All_Position_0[i].begin() + PerCluster_Num[i], All_Position_0[i].end());
		//	i++;
		//}
	}

}