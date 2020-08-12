#pragma once

#define Latitude 0
#define Logitude 1
#define Mark_ES 2
#define Real_Distance 3
#define O_Distance 4
#define Core_Num 5
#define Load_Rate 6

using namespace std;
#include<iostream>
#include<vector>
#include<algorithm>


extern double Return_Attribute[239]; //����Get_Master_Three_Vector_Attribute���ص������������׵�ַ

extern int Which_RSU_In_Group_Is_ES[50];  // ÿ��ES�ڸ��Ե������ǵڼ���
extern int Core_Num_Per_ES_Array[50];  // ÿ��ES�ж��ٺ�
extern double Load_Rate_Per_ES_Arrary[50];  // ÿһ�����и����ʵĺ�

/* �������л�ȡ���� */
extern double *Get_Master_Three_Vector_Attribute(vector<vector<vector<double>>> Three_Dimension_Vector, int Which_Attribute);
/*��ȡÿ��ES�����*/
int *Get_Which_RSU_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector);
/*get RSU ����һ��ĵڼ���*/
int *Get_Which_RSU_In_Group_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector);
/* ����һ�������׵�ַ��������д��ÿ��ES�ж��ٺ�*/
int *Core_Num_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector);
/* ����һ�������׵�ַ��������д����һ�����и����ʵĺ�*/
double *Load_Rate_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector);








