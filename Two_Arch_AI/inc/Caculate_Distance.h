#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
using namespace std;
#include <vector>




/* caculate the real distance of two positions based on latitude and longitude */
double Caculate_Real_Distance(vector<double> p1, vector<double> p2);
/*����Get_Distance�������õĽ�ʮ���Ƶľ�γ������Ϊʵ�ʾ�����㷨������������Ҫ�ɵ���
���ݽ���������������������������������꣬��һ�������ʾ��ʮ���ƣ�γ�ȣ��ڶ��������ʾ��ʮ���ƣ�����*/

/* caculate the ou_shi distance of two positions based on latitude and longitude */
double Caculate_O_Distance(vector<double> p1, vector<double> p2);

