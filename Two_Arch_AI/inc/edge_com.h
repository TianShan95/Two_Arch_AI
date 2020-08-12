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





#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0600     // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

using namespace std;

extern int ES_Num = 39;//边缘服务器ES的数量为39个
extern const int Node_Num = 239;//节点RSU的数量为239个
extern const int Time_Per_ES_Works = 12;  // 每个ES工作的时间，假设时间不变，用于通过功率求能耗用的
extern const int Trans_Speed = 500000;//传输速率500Kb/s
extern const int Prop_Speed = 2 * pow(10, 8);//传播速率,int占4个字节，2*pow(10,8)不会溢出
extern double Per_ES_HandleData_Speed;//每个ES处理数据包的速率
extern const int Per_Core_HandleData_Speed = 10;//每个核单位时间处理数据包的个数
extern const int Per_CorePower_Max = 45;//单个核的最大工作阀值
extern const int ES_Core_Max = 32;//边缘服务器的核的最大值
extern const int P_Idle = 300;//服务器在空闲状态下的功率
extern const int P_Full = 495;//服务器在满状态下时的功率
extern const int Per_Core_Price = 5;//每个处理器的价格
extern const double Per_ES_Max_R = 5000;//每个ES的覆盖范围半径为5km

extern vector<vector<double>> Distance_RSU_To_Cloud_Server;
extern double Accumulate_Load_Rate_Of_One_Group;
extern vector<double>Total_Request_Per_ES(39);


extern int *Which_RSU_Is_ES;  // 每个ES在RSU编号里的顺序

int edge_com();


