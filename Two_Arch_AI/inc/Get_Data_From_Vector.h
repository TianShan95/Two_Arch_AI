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


extern double Return_Attribute[239]; //这是Get_Master_Three_Vector_Attribute返回的是这个数组的首地址

extern int Which_RSU_In_Group_Is_ES[50];  // 每个ES在各自的类中是第几个
extern int Core_Num_Per_ES_Array[50];  // 每个ES有多少核
extern double Load_Rate_Per_ES_Arrary[50];  // 每一类所有负载率的和

/* 从容器中获取属性 */
extern double *Get_Master_Three_Vector_Attribute(vector<vector<vector<double>>> Three_Dimension_Vector, int Which_Attribute);
/*获取每个ES的序号*/
int *Get_Which_RSU_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector);
/*get RSU 是哪一类的第几个*/
int *Get_Which_RSU_In_Group_Is_ES(vector<vector<vector<double>>> Three_Dimension_Vector);
/* 返回一个数组首地址，数组里写着每个ES有多少核*/
int *Core_Num_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector);
/* 返回一个数组首地址，数组里写着这一类所有负载率的和*/
double *Load_Rate_Per_ES_Function(vector<vector<vector<double>>> Three_Dimension_Vector);








