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
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // ����ÿһ��
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


int *Get_Which_RSU_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector)  // ����ÿ��ES�������
{
	int index = 0;  // ������ÿ��ÿ���ı���
	int i = 0;

	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // ����ÿһ��
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

// ����ES��ÿһ���е����
int *Get_Which_RSU_In_Group_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector)  //����ÿ��ES���ǵڼ���ĵڼ���������Ŀ�꺯����д
{
	int index = 0;  // ������ÿ��ÿ���ı���
	int i = 0;  //��������ĵڼ���
	int j = 0;  // ��ʾ����һ��ĵڼ���
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		j = 0;
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // ����ÿһ��
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

/**************************************�����������ÿ��ES�ĺ���*****************************************/
int *Core_Num_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector)  // ����һ�������׵�ַ��������д��ÿ��ES�ж��ٺ�
{
	int index = 0;  // ������ÿ��ÿ���ı���
	int i = 0;  // ��������ĵڼ���
	int j = 0;  // ��ʾ����һ��ĵڼ���
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		j = 0;
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // ����ÿһ��
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


/**************************************�����������ÿ��ES�ĺ���*****************************************/
double *Load_Rate_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector)  // ����һ�������׵�ַ��������д����һ�����и����ʵĺ�
{
	double accumulate_load_rate = 0;  // �ۼӸ����ʱ���
	int index = 0;  // ������ÿ������ÿ������ı�����˳���1��239�������239������
	int i = 0;  // ��������ĵڼ���
	int j = 0;  // ��ʾ����һ��ĵڼ���
	for (vector<vector<vector<double>>>::iterator it = Three_Dimension_Vector.begin(); it != Three_Dimension_Vector.end(); it++)
	{
		j = 1;
		for (vector<vector<double>>::iterator itt = (*it).begin(); itt != (*it).end(); itt++)  // ����ÿһ��
		{
			accumulate_load_rate += (*itt).at(6);
			//cout << "accumulate_load_rate " << j << " " << accumulate_load_rate << endl;
			//cout << "index:  " << index << endl;  // �ܵ���˵�ǵڼ���
			//if (index == 16)
			//{
			//	break;
			//}
			if (j >= PerCluster_Num[i])
			{
				Load_Rate_Per_ES_Arrary[i] = accumulate_load_rate;
				accumulate_load_rate = 0;
				//cout << "index:  " << index << endl;  // �ܵ���˵�ǵڼ���
				//cout << "i:  " << i << endl;   // д������ڼ���Ԫ����
				//cout << "j:  " << j << endl;  //  �ڵ�ǰ������˵�ڼ���
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