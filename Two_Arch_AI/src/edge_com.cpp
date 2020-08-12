#include"Init.h"
/*********************************************************************************
Copyright:Aaron95
Author:田山
Date:2020-06-25
Description:边缘服务器部署优化
************************************************************************************/


/***
 *                  ___====-_  _-====___
 *            _--^^^#####//      \\#####^^^--_
 *         _-^##########// (    ) \\##########^-_
 *        -############//  |\^^/|  \\############-
 *      _/############//   (@::@)   \\############\_
 *     /#############((     \\//     ))#############\
 *    -###############\\    (oo)    //###############-
 *   -#################\\  / VV \  //#################-
 *  -###################\\/      \//###################-
 * _#/|##########/\######(   /\   )######/\##########|\#_
 * |/ |#/\#/\#/\/  \#/\##\  |  |  /##/\#/  \/\#/\#/\#| \|
 * `  |/  V  V  `   V  \#\| |  | |/#/  V   '  V  V  \|  '
 *    `   `  `      `   / | |  | | \   '      '  '   '
 *                     (  | |  | |  )
 *                    __\ | |  | | /__
 *                   (vvv(VVV)(VVV)vvv)
 *                        神兽保佑
 *                       代码无BUG!
 */

int ES_Num = 39;//边缘服务器ES的数量为39个
const int Node_Num = 239;//节点RSU的数量为239个
const int Time_Per_ES_Works = 12;
const int Trans_Speed = 500000;//传输速率500Kb/s
const int Prop_Speed = 2*pow(10,8);//传播速率,int占4个字节，2*pow(10,8)不会溢出
double Per_ES_HandleData_Speed;//每个ES处理数据包的速率
const int Per_Core_HandleData_Speed = 10;//每个核单位时间处理数据包的个数
const int Per_CorePower_Max = 45;//单个核的最大工作阀值
const int ES_Core_Max;//边缘服务器的核的最大值
const int P_Idle = 300;//服务器在空闲状态下的功率
const int P_Full = 495;//服务器在满状态下时的功率
const int Per_Core_Price = 5;//每个处理器的价格
const double Per_ES_Max_R = 5000;//每个ES的覆盖范围半径为5km

vector<vector<double>>Distance_RSU_To_Cloud_Server(ES_Num);  // 所有rsu到云服务器的距离
vector<double>Handle_Task_Rate_Per_ES(ES_Num);  // 每个边缘服务器的处理任务率

int n = 100;  // 也就是解得个数
vector<vector<vector<vector<double>>>> pop(n);// 这是种群容器，里面存放着所有符合条件的解，如果解出来的解符合，就会存放其中

int Have_Done_The_Num_Of_RSU[39];  // 这个数组存放已经分配了的RSU，为了打印在屏幕上便于观察

double *Num_Of_Core_Per_ES;  // 定义一个全局指针，edge_com函数里让它指向每个ES核数的首地址，可访问ES的核数信息

int *Which_RSU_Is_ES;  // 定义一个全局指针，里面存放着ES在所有数据中是第几个，是ES在所有RSU中的总排序

double *Real_Distance_Between_RSU_To_ES;  // 第一一个全局指针，指向每个RSU好它那一类的ES的真实距离

double *Total_Load_Rate_Per_ES;  // 这是指向每个ES总的负载率的指针

vector<vector<double>> Cloud_Server_Position(3);  	//定义一个向量，里面是云服务器的经纬度，此程序只有一个云服务器

int m = 4;  // 目标的个数

/*向量obj是目标函数obj_com返回来的目标值，因为每次进化后的目标值都会被重新计算，所以说这个向量是二维的*/
vector<vector<double>>obj;

/*向量cobj和obj的含义一样，这个向量是在一代一代的循环（while循环）里用到的*/
vector<vector<double>> cobj;

vector<double>Total_Request_Per_ES(39);  // 存放每个ES所管辖的所有RSU之和

double Accumulate_Load_Rate_Of_One_Group = 0;//中间中间变量
int edge_com()

{


	for (int i = 0; i < All_Position.size(); i++)
	{
		for (int j = 0; j < All_Position[i].size(); j++)
		{
			Accumulate_Load_Rate_Of_One_Group += All_Position[i][j][4];
		}
		Total_Request_Per_ES[i] = Accumulate_Load_Rate_Of_One_Group;
		Accumulate_Load_Rate_Of_One_Group = 0;
	}  // 计算每个es的总请求率, 计算方法是ES所在类的所有RSU的负载率之和
	
	/**********************已经分配了的RSU的数量*****************/
	/*数组里每个数是已分配了的RSU的个数,应该是为了便于观察*/
	Have_Done_The_Num_Of_RSU[0] = PerCluster_Num[0];  // Initialize the first element
	for (int i = 1; i < 39; i++)
	{
		Have_Done_The_Num_Of_RSU[i] = PerCluster_Num[i] + Have_Done_The_Num_Of_RSU[i - 1];
		cout << Have_Done_The_Num_Of_RSU[i] << endl;
	}



	/***************这个数组里是每个ES核的个数，RSU核的个数为0*********************/
	Num_Of_Core_Per_ES = Get_Master_Three_Vector_Attribute(All_Position, Core_Num);


	/***************获取ES的序号在所有RSU中排第几******************************************/
	Which_RSU_Is_ES = Get_Which_RSU_Is_ES(All_Position);

	
	/***************每个rsu节点到相应类的es的真实距离******************************************/
	Real_Distance_Between_RSU_To_ES = Get_Master_Three_Vector_Attribute(All_Position, Real_Distance);


	
	/***********************每个ES所管辖的所有RSU的负载率************************/
	Total_Load_Rate_Per_ES = Load_Rate_Per_ES_Function(All_Position);


	/**********************计算每个边缘服务器的处理任务率*************************/
	for (int i = 0; i < ES_Num; ++i)
	{
		if (45 * Num_Of_Core_Per_ES[i] > Total_Load_Rate_Per_ES[i]) {
			Handle_Task_Rate_Per_ES[i] = 1;
		}
		else
		{
			Handle_Task_Rate_Per_ES[i] = 45 * Num_Of_Core_Per_ES[i] / Total_Load_Rate_Per_ES[i];
		}

	}  




	for (int i = 0; i < 3; i++)
	{
		Cloud_Server_Position[i].resize(2);
	}
	double cloud_position[2] = { 39.491, 116.552 };
	/*使用迭代器方式赋值*/
	for (auto it_vv = Cloud_Server_Position.begin(); it_vv != Cloud_Server_Position.end(); ++it_vv)
	{
		int for_1 = 0;
		for (auto it_v = it_vv->begin(); it_v != it_vv->end(); it_v++) { //迭代器的使用方法和指针类似
			*it_v = cloud_position[for_1];
			for_1++;
		}
	}
	/***************求rsu到云的距离*************************/
	for (int i = 0; i < All_Position.size(); i++)
	{
		Distance_RSU_To_Cloud_Server[i].resize(ES_Num);
		for (int j = 0; j < All_Position[i].size(); j++)
		{
			Distance_RSU_To_Cloud_Server[i][j] = Caculate_O_Distance(All_Position[i][j], Cloud_Server_Position[0]);
			
		}

	}


	 
	
	/***************如果算出来的解符合条件就加到pop种群里********************/
	if (Constraint(All_Position, Num_Of_Core_Per_ES))
	{
		pop.push_back(All_Position);

	}

	


	
	obj = obj_com(pop, Handle_Task_Rate_Per_ES);
	vector<vector<double>>DAobj(obj);  // 复制一个obj副本给DAobj（多样性存档）
	vector<vector<vector<vector<double>>>>DA, cpop, npop;

	DA = find_nodom_ai(pop, obj, DAobj, m);  // 返回一个最优的存档


		double sum1[4];
	for (int j = 0; j < m; ++j) 
	{
		sum1[j] = 0;
		for (int i = 0; i < n; i++) {
			sum1[j] += obj[i][j];
		}
	}
	for (int j = 0; j < 5; ++j) 
	{
		cout << sum1[j] / n << "  ";
	}
	cout << endl;
	int g = 0;
	while (g < 300) {
		clock_t s1 = clock();
		cpop = SBXAI(pop, DA, obj, DAobj, n, m, Num_Of_Core_Per_ES);  // continue pop，应该是每一次进化生出来的种群
		cobj = obj_com(cpop, Handle_Task_Rate_Per_ES);
		vector<vector<double>>nobj (cobj);
		npop = find_nodom_ai(cpop, cobj, nobj, m);
		updateCA(cpop, pop, cobj, obj);//YU,obj,pop,all updated
		updateDA(npop, DA, nobj, DAobj);//DA,DAobj,all updated
		cout << DA.size() << "cost time " << clock() - s1 << "ms" << endl;
		g++;
	}
	return 1;
}