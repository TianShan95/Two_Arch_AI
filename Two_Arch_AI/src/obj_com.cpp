#include"Init.h"

/*目标函数，传进来形参，返回一个容器*/
vector<vector<double>> obj_com(vector<vector<vector<vector<double>>>>&pop,\
								vector<double> Handle_Task_Rate_Per_ES)
{
	vector<double>q1(Group_Size, 0);
	double T = 0;
	double T1 = 0;
	vector<double> TTrans_Speed(Node_Num);//rj向ei传输数据得传输时延
	vector<double> Tprop1(Node_Num);//rj向ei传输数据得传播时延
	vector<double> Tprop2(Node_Num);//rj向云服务器的传播时延
	vector<double> Tqueue(ES_Num);//rj向ei传输数据得队列时间
	vector<int>which(Node_Num);//RSU分配到es还是云服务器，1分配到es，0到云

	vector<double>m1(Group_Size);//定义中间变量m1
	vector<double>m2(Group_Size, 1);//定义中间变量m2
	vector<double>m3(Group_Size, 1);//定义中间变量m3
	vector<double>m4(Group_Size, 1);//定义中间变量m4
	vector<double>m5(Group_Size, 1);//定义中间变量m5
	vector<double>m6(Group_Size);//定义中间变量m6
	vector<double>m7(Group_Size, 0);//定义中间变量m7

	int *Core_Num_Per_ES;  // 这是接每个ES处理器个数的指针
	Core_Num_Per_ES = Core_Num_Per_ES_Function(All_Position);

	double *Total_Load_Rate_Per_ES;  // 这是接每个ES总的负载率的指针
	Total_Load_Rate_Per_ES = Load_Rate_Per_ES_Function(All_Position);

	double *Load_Rate_Per_RSU;  // 存每个RSU(每个节点负载率)的指针
	Load_Rate_Per_RSU = Get_Master_Three_Vector_Attribute(All_Position, Load_Rate);


	vector<vector<double>>obj(pop.size());
	for (int i = 0; i < pop.size(); i++)//给存放目标变量的容器分配容量 --Aaron
	{
		obj[i].resize(5);
	}



	for (int i = 0; i < Group_Size; ++i) {

		m1[i] = Handle_Task_Rate_Per_ES[i] * Total_Load_Rate_Per_ES[i] / 10;
			for (int j = 0; j < Core_Num_Per_ES[i]; ++j)
			{
				m2[i] *= Core_Num_Per_ES[i] * m1[i];
				m3[i] *= Core_Num_Per_ES[i] - 1;

			}
		for (int j = 0; j < Core_Num_Per_ES[i] - 1; ++j)
		{
			for (int l = 0; l < j; ++l)
			{
				m4[i] *= Core_Num_Per_ES[i] * m1[i];
				m5[i] *= j - 1;
				m6[i] = m4[i] / m5[i];
			}
			m7[i] += m6[i];
		}

	}
	for (int i = 0; i < Group_Size; ++i)
	{
		Tqueue[i] = m2[i] / m3[i] / (1 - m1[i]) / (m7[i] + m2[i] / m3[i] / (1 - m1[i]));//计算排列时间

	}
	for (int i = 0; i < Group_Size; ++i)
	{
		TTrans_Speed[i] = Load_Rate_Per_RSU[i] / Trans_Speed; 
	}//ES到云服务器的传输时间
	vector<double>TCl(Node_Num);//数据直接传输到云的RSU的延迟
	for (int i = 0; i < All_Position.size; i++)
	{
		for(int j = 0; j < All_Position[i].size;j++)
		Tprop2[i] = Distance_RSU_To_Cloud_Server[i][j] / Prop_Speed;

		TCl[i] = TTrans_Speed[i] + Tprop2[i];
	}//计算rsu到云服务器的传播速率及总延迟


	for (int i = 0; i < Node_Num; ++i)
	{
		if (TCl[i] > (TTrans_Speed[i] + Tprop2[i] + Tqueue[i]))
		{
			which[i] = 1;
		}
		else
		{
			which[i] = 0;
		}

	}//RSU卸载到云服务器还是边缘服务器
	for (int i = 0; i < Group_Size; ++i) {
		for (int j = 0; j < Node_Num; ++j)
		{
			if (which[j] = 1)
			{
				q1[i] += (TTrans_Speed[i] + Tprop1[i] + Tqueue[i])*Handle_Task_Rate_Per_ES[i] + \
						 (1 - Handle_Task_Rate_Per_ES[i])*TCl[i];
			}

		}
		T1 += q1[i];
	}
	T = T1 / Node_Num;//目标一


	double Total_Load_Rate = 0;  // Total load rate of all RSU
	double Mean_Load_Rate;  // The average load rate
	double Sum_1_Thrid_Goal = 0;  // intermediate variable Sum1
	double Sum_2_Thrid_Goal = 0;  // intermediate variable Sum2
	double Fload;
	for (int i = 0; i < Group_Size; ++i)
	{
		Sum_1_Thrid_Goal += Total_Load_Rate_Per_ES[i];
	}

	Mean_Load_Rate = Sum_1_Thrid_Goal / Group_Size;
	for (int i = 0; i < Group_Size; ++i)
	{
		Sum_2_Thrid_Goal += (Total_Load_Rate_Per_ES[i] - Mean_Load_Rate)*(Total_Load_Rate_Per_ES[i] - Mean_Load_Rate);

	}
	Fload = sqrt(Sum_2_Thrid_Goal / Group_Size);//目标二


	vector<double>Power_Per_ES(Group_Size);  // 定义边缘服务器在t个单位时间的功耗
	vector<double>Energy_Per_ES(Group_Size);  // 定义边缘服务器在t个单位时间的能耗
	double Energy_Total = 0;
	for (int i = 0; i < Group_Size; i++)
	{
		if (Total_Load_Rate_Per_ES[i] < Per_CorePower_Max)
		{
			Power_Per_ES[i] = P_Idle + (P_Full - P_Idle)*Total_Load_Rate_Per_ES[i] / Core_Num_Per_ES[i] / Per_CorePower_Max;

		}
		else
		{
			Power_Per_ES[i] = P_Full;
		}
		Energy_Per_ES[i] = Power_Per_ES[i] * Time_Per_ES_Works;
		Energy_Total += Energy_Per_ES[i];
	}
	//目标三，求所有ES的总能耗最小



	vector<vector<int> >If_Covered_By_ES(Node_Num);  // Mark The RSU If Coverd by ES
	double Sum_RSU_Cover_By_ES = 0;  // Caculated the sum of RSU which is Coverd by ES
	double Real_Distance_RSU_To_Every_ES;  // 计算每个RSU到所有ES的距离

	for (int i = 0; i < Group_Size; i++)  // This RSU belong to which Group
	{
		for (int j = 0; j < PerCluster_Num[i]; j++)  // This RSU is belong to which one of this group
		{
			for (int k = 0; k < Group_Size; k++)  // allow this RSU is caculated with every ES
			{
				Real_Distance_RSU_To_Every_ES = Caculate_Real_Distance(All_Position[i][j], \
					All_Position[k][Which_RSU_In_Group_Is_ES[k]]);  // 计算距离
				if (Real_Distance_RSU_To_Every_ES <= Per_ES_Max_R)  // If the RSU is covered
				{
					If_Covered_By_ES[i][j] = 1;
				}
				else 
				{
					If_Covered_By_ES[i][j] = 0;
				}
			}
		}
	}

	for (int i = 0; i < Node_Num; i++)
	{
		for (int j = 0; j < Group_Size; j++)
		{
			Sum_RSU_Cover_By_ES += If_Covered_By_ES[i][j];
		}
	}  // 目标四，让所有RSU被ES覆盖的总数最多





	for (int u = 0;u < pop.size(); u++)  // u express which evolutional round
	{
		obj[u][0] = T;
		obj[u][1] = Fload;
		obj[u][2] = Energy_Total;  // The third goal
		obj[u][3] = Sum_RSU_Cover_By_ES / Node_Num / Node_Num;  // The Fourth goal
	}
	return obj;
}





