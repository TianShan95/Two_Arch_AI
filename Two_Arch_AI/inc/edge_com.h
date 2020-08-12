#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
#include<iostream>
#include <vector>

#include"Generate_Rand.h"
#include"obj_com.h"
#include"updateCA.h"
#include"updateDA.h"
#include"SBX.h"
#include"SBX_AI.h"
#include"com_obj.h"
#include"Constraint.h"
#include"find_nodom.h"
#include"dom.h"
#include"fitness.h"
#include"environment_select.h"
#include"mutation.h"





#ifndef _WIN32_WINNT            // ָ��Ҫ������ƽ̨�� Windows Vista��
#define _WIN32_WINNT 0x0600     // ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

using namespace std;

extern int ES_Num = 39;//��Ե������ES������Ϊ39��
extern const int Node_Num = 239;//�ڵ�RSU������Ϊ239��
extern const int Time_Per_ES_Works = 12;  // ÿ��ES������ʱ�䣬����ʱ�䲻�䣬����ͨ���������ܺ��õ�
extern const int Trans_Speed = 500000;//��������500Kb/s
extern const int Prop_Speed = 2 * pow(10, 8);//��������,intռ4���ֽڣ�2*pow(10,8)�������
extern double Per_ES_HandleData_Speed;//ÿ��ES�������ݰ�������
extern const int Per_Core_HandleData_Speed = 10;//ÿ���˵�λʱ�䴦�����ݰ��ĸ���
extern const int Per_CorePower_Max = 45;//�����˵��������ֵ
extern const int ES_Core_Max = 32;//��Ե�������ĺ˵����ֵ
extern const int P_Idle = 300;//�������ڿ���״̬�µĹ���
extern const int P_Full = 495;//����������״̬��ʱ�Ĺ���
extern const int Per_Core_Price = 5;//ÿ���������ļ۸�
extern const double Per_ES_Max_R = 5000;//ÿ��ES�ĸ��Ƿ�Χ�뾶Ϊ5km

extern vector<vector<double>> Distance_RSU_To_Cloud_Server;
extern double Accumulate_Load_Rate_Of_One_Group;
extern vector<double>Total_Request_Per_ES(39);


extern int *Which_RSU_Is_ES;  // ÿ��ES��RSU������˳��

int edge_com();


