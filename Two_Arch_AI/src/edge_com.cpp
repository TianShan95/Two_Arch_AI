#include"Init.h"
/*********************************************************************************
Copyright:Aaron95
Author:��ɽ
Date:2020-06-25
Description:��Ե�����������Ż�
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
 *                        ���ޱ���
 *                       ������BUG!
 */

int ES_Num = 39;//��Ե������ES������Ϊ39��
const int Node_Num = 239;//�ڵ�RSU������Ϊ239��
const int Time_Per_ES_Works = 12;
const int Trans_Speed = 500000;//��������500Kb/s
const int Prop_Speed = 2*pow(10,8);//��������,intռ4���ֽڣ�2*pow(10,8)�������
double Per_ES_HandleData_Speed;//ÿ��ES�������ݰ�������
const int Per_Core_HandleData_Speed = 10;//ÿ���˵�λʱ�䴦�����ݰ��ĸ���
const int Per_CorePower_Max = 45;//�����˵��������ֵ
const int ES_Core_Max;//��Ե�������ĺ˵����ֵ
const int P_Idle = 300;//�������ڿ���״̬�µĹ���
const int P_Full = 495;//����������״̬��ʱ�Ĺ���
const int Per_Core_Price = 5;//ÿ���������ļ۸�
const double Per_ES_Max_R = 5000;//ÿ��ES�ĸ��Ƿ�Χ�뾶Ϊ5km

vector<vector<double>>Distance_RSU_To_Cloud_Server(ES_Num);  // ����rsu���Ʒ������ľ���
vector<double>Handle_Task_Rate_Per_ES(ES_Num);  // ÿ����Ե�������Ĵ���������

int n = 100;  // Ҳ���ǽ�ø���
vector<vector<vector<vector<double>>>> pop(n);// ������Ⱥ�����������������з��������Ľ⣬���������Ľ���ϣ��ͻ�������

int Have_Done_The_Num_Of_RSU[39];  // ����������Ѿ������˵�RSU��Ϊ�˴�ӡ����Ļ�ϱ��ڹ۲�

double *Num_Of_Core_Per_ES;  // ����һ��ȫ��ָ�룬edge_com����������ָ��ÿ��ES�������׵�ַ���ɷ���ES�ĺ�����Ϣ

int *Which_RSU_Is_ES;  // ����һ��ȫ��ָ�룬��������ES�������������ǵڼ�������ES������RSU�е�������

double *Real_Distance_Between_RSU_To_ES;  // ��һһ��ȫ��ָ�룬ָ��ÿ��RSU������һ���ES����ʵ����

double *Total_Load_Rate_Per_ES;  // ����ָ��ÿ��ES�ܵĸ����ʵ�ָ��

vector<vector<double>> Cloud_Server_Position(3);  	//����һ���������������Ʒ������ľ�γ�ȣ��˳���ֻ��һ���Ʒ�����

int m = 4;  // Ŀ��ĸ���

/*����obj��Ŀ�꺯��obj_com��������Ŀ��ֵ����Ϊÿ�ν������Ŀ��ֵ���ᱻ���¼��㣬����˵��������Ƕ�ά��*/
vector<vector<double>>obj;

/*����cobj��obj�ĺ���һ���������������һ��һ����ѭ����whileѭ�������õ���*/
vector<vector<double>> cobj;

vector<double>Total_Request_Per_ES(39);  // ���ÿ��ES����Ͻ������RSU֮��

double Accumulate_Load_Rate_Of_One_Group = 0;//�м��м����
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
	}  // ����ÿ��es����������, ���㷽����ES�����������RSU�ĸ�����֮��
	
	/**********************�Ѿ������˵�RSU������*****************/
	/*������ÿ�������ѷ����˵�RSU�ĸ���,Ӧ����Ϊ�˱��ڹ۲�*/
	Have_Done_The_Num_Of_RSU[0] = PerCluster_Num[0];  // Initialize the first element
	for (int i = 1; i < 39; i++)
	{
		Have_Done_The_Num_Of_RSU[i] = PerCluster_Num[i] + Have_Done_The_Num_Of_RSU[i - 1];
		cout << Have_Done_The_Num_Of_RSU[i] << endl;
	}



	/***************�����������ÿ��ES�˵ĸ�����RSU�˵ĸ���Ϊ0*********************/
	Num_Of_Core_Per_ES = Get_Master_Three_Vector_Attribute(All_Position, Core_Num);


	/***************��ȡES�����������RSU���ŵڼ�******************************************/
	Which_RSU_Is_ES = Get_Which_RSU_Is_ES(All_Position);

	
	/***************ÿ��rsu�ڵ㵽��Ӧ���es����ʵ����******************************************/
	Real_Distance_Between_RSU_To_ES = Get_Master_Three_Vector_Attribute(All_Position, Real_Distance);


	
	/***********************ÿ��ES����Ͻ������RSU�ĸ�����************************/
	Total_Load_Rate_Per_ES = Load_Rate_Per_ES_Function(All_Position);


	/**********************����ÿ����Ե�������Ĵ���������*************************/
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
	/*ʹ�õ�������ʽ��ֵ*/
	for (auto it_vv = Cloud_Server_Position.begin(); it_vv != Cloud_Server_Position.end(); ++it_vv)
	{
		int for_1 = 0;
		for (auto it_v = it_vv->begin(); it_v != it_vv->end(); it_v++) { //��������ʹ�÷�����ָ������
			*it_v = cloud_position[for_1];
			for_1++;
		}
	}
	/***************��rsu���Ƶľ���*************************/
	for (int i = 0; i < All_Position.size(); i++)
	{
		Distance_RSU_To_Cloud_Server[i].resize(ES_Num);
		for (int j = 0; j < All_Position[i].size(); j++)
		{
			Distance_RSU_To_Cloud_Server[i][j] = Caculate_O_Distance(All_Position[i][j], Cloud_Server_Position[0]);
			
		}

	}


	 
	
	/***************���������Ľ���������ͼӵ�pop��Ⱥ��********************/
	if (Constraint(All_Position, Num_Of_Core_Per_ES))
	{
		pop.push_back(All_Position);

	}

	


	
	obj = obj_com(pop, Handle_Task_Rate_Per_ES);
	vector<vector<double>>DAobj(obj);  // ����һ��obj������DAobj�������Դ浵��
	vector<vector<vector<vector<double>>>>DA, cpop, npop;

	DA = find_nodom_ai(pop, obj, DAobj, m);  // ����һ�����ŵĴ浵


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
		cpop = SBXAI(pop, DA, obj, DAobj, n, m, Num_Of_Core_Per_ES);  // continue pop��Ӧ����ÿһ�ν�������������Ⱥ
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