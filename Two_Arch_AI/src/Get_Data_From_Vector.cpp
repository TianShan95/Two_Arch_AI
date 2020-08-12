#include"Get_Data_From_Vector.h"
#include"Init.h"
double Return_Attribute[239];
int Which_RSU_Is_ES[50];
int Which_RSU_In_Group_Is_ES[50];
int Core_Num_Per_ES_Array[50];
double Load_Rate_Per_ES_Arrary[50];



double* Get_Master_Three_Vector_Attribute(vector<vector<vector<double>>> Three_Dimension_Vector, int Which_Attribute)
{
	int index = 0;
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // 遍历每一行
		{
			Return_Attribute[index++] = (*itt).at(Which_Attribute);
		}
	}

	//cout << "****" << endl;
	//for (int k = 0; k < 239; k++)
	//{
	//	cout << " " << Load_Rate[k] << endl;
	//}
	//cout << "****" << endl;
	return Return_Attribute;

}


int *Get_Which_RSU_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector)  // 这是每个ES的总序号
{
	int index = 0;  // 向量里每个每个的遍历
	int i = 0;

	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // 遍历每一行
		{
			Return_Attribute[index] = (*itt).at(2);
			if (Return_Attribute[index] == 1)
			{
				Which_RSU_Is_ES[i] = index;
			}
			index++;
		}
	}
	return Which_RSU_Is_ES;
}

// 这是ES在每一类中的序号
int *Get_Which_RSU_In_Group_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector)  //返回每个ES，是第几类的第几个，方便目标函数书写
{
	int index = 0;  // 向量里每个每个的遍历
	int i = 0;  //返回数组的第几个
	int j = 0;  // 表示是这一类的第几个
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		j = 0;
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // 遍历每一行
		{
			Return_Attribute[index] = (*itt).at(2);
			if (Return_Attribute[index] == 1)
			{
				Which_RSU_Is_ES[i] = j;
				//cout << "index:  " << index << endl;
				//cout << "i:  " << i << endl;
				//cout << "j:  " << j << endl;
				//cout << "Which_RSU_In_Group_Is_ES:   " << Which_RSU_In_Group_Is_ES[j] << endl;
				i++;
			}
			j++;
			index++;
		}
	}
	//for (int j = 0; j < 39; j++)
	//{
	//	cout << " " << Which_RSU_In_Group_Is_ES[j] << endl;
	//}
	return Which_RSU_In_Group_Is_ES;
}

/**************************************这个函数返回每个ES的核数*****************************************/
int *Core_Num_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector)  // 返回一个数组首地址，数组里写着每个ES有多少核
{
	int index = 0;  // 向量里每个每个的遍历
	int i = 0;  // 返回数组的第几个
	int j = 0;  // 表示是这一类的第几个
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		j = 0;
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // 遍历每一行
		{
			Return_Attribute[index] = (*itt).at(2);
			if (Return_Attribute[index] == 1)
			{
				Core_Num_Per_ES_Array[i] = Three_Dimension_Vector[i][j][5];
				//cout << "index:  " << index << endl;
				//cout << "i:  " << i << endl;
				//cout << "j:  " << j << endl;
				//cout << "Core_Num_Per_ES_Array:   " << Core_Num_Per_ES_Array[j] << endl;
				i++;
			}
			j++;
			index++;
		}
	}
	//for (int j = 0; j < 39; j++)
	//{
	//	cout << " " << Which_RSU_In_Group_Is_ES[j] << endl;
	//}
	return Core_Num_Per_ES_Array;
}


/**************************************这个函数返回每个ES的核数*****************************************/
double *Load_Rate_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector)  // 返回一个数组首地址，数组里写着这一类所有负载率的和
{
	double accumulate_load_rate = 0;  // 累加负载率变量
	int index = 0;  // 向量里每个个体每个个体的遍历，顺序从1到239，如果有239个个体
	int i = 0;  // 返回数组的第几个
	int j = 0;  // 表示是这一类的第几个
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		j = 1;
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // 遍历每一行
		{
			accumulate_load_rate += (*itt).at(6);
			//cout << "accumulate_load_rate " << j << " " << accumulate_load_rate << endl;
			//cout << "index:  " << index << endl;  // 总的来说是第几个
			//if (index == 16)
			//{
			//	break;
			//}
			if (j >= PerCluster_Num[i])
			{
				Load_Rate_Per_ES_Arrary[i] = accumulate_load_rate;
				accumulate_load_rate = 0;
				//cout << "index:  " << index << endl;  // 总的来说是第几个
				//cout << "i:  " << i << endl;   // 写到数组第几个元素了
				//cout << "j:  " << j << endl;  //  在当前类里来说第几个
				//cout << "Load_Rate_Per_ES_Arrary[i]:   " << Load_Rate_Per_ES_Arrary[i] << endl;
				//cout << " PerCluster_Num[i]  " << PerCluster_Num[i] << endl;
				i++;
			}
			j++;
			index++;
		}
	}
	//for (int j = 0; j < 39; j++)
	//{
	//	cout << " " << Which_RSU_In_Group_Is_ES[j] << endl;
	//}
	return Load_Rate_Per_ES_Arrary;
}