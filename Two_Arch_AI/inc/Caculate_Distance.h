#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
using namespace std;
#include <vector>




/* caculate the real distance of two positions based on latitude and longitude */
double Caculate_Real_Distance(vector<double> p1, vector<double> p2);
/*这是Get_Distance函数调用的将十进制的经纬度运算为实际距离的算法，其他函数需要可调用
传递进来的是两个向量，向量里包含两个坐标，第一个坐标表示（十进制）纬度，第二个坐标表示（十进制）经度*/

/* caculate the ou_shi distance of two positions based on latitude and longitude */
double Caculate_O_Distance(vector<double> p1, vector<double> p2);

