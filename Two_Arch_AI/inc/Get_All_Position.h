#pragma once


#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
using namespace std;
#include <vector>


extern int PerCluster_Num[50];
vector<vector<vector<double>>> Get_All_Position();
/*这是为了读取外部文件的，不需要重新调用*/
extern vector<vector<vector<double>>> All_Position;  // 生命全局变量All_Position


extern const int Group_Size;



