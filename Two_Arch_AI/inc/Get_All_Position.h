#pragma once


#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
using namespace std;
#include <vector>


extern int PerCluster_Num[50];
vector<vector<vector<double>>> Get_All_Position();
/*����Ϊ�˶�ȡ�ⲿ�ļ��ģ�����Ҫ���µ���*/
extern vector<vector<vector<double>>> All_Position;  // ����ȫ�ֱ���All_Position


extern const int Group_Size;



