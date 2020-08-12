#include "Get_All_Position.h"

int PerCluster_Num[50];
vector<vector<vector<double>>> All_Position;
const int Group_Size = 39;

vector<vector<vector<double>>> Get_All_Position()
{
	
	All_Position.resize(Group_Size);
	
	ifstream ifs;
	for (int i = 0; i < Group_Size; i++)  // i express which file
	{
		string file = "D:\\temp\\Result_Out_";
		file += to_string(100 + i);
		file += ".txt";
		//cout << file << endl;
		ifs.open(file, ios::in);
		string buff;
		if (!ifs)
		{
			cout << "打开失败" << endl;
		}
		int j = 0;  // express which row
		All_Position[i].resize(20);
		while (getline(ifs, buff))
		{
			//cout << str<<endl;

			char *saveptr;
			char *s_input = (char *)buff.c_str();
			const char * split = " ";
			// 以‘ ’为分隔符拆分字符串
			char *p = strtok_s(s_input, split, &saveptr);
			double a;
			while (p != NULL) {
				// char * -> int
				a = atof(p);
				//cout << a << endl;
				All_Position[i][j].push_back(a);
				p = strtok_s(NULL, split, &saveptr);
			}//end while


			//int index = str.find(' ');
			//istringstream iss(str.substr(0, buff));
			//double l, r;
			//iss >> l;
			//istringstream isr(str.substr(index + 1));
			//isr >> r;
			//cout << "left: " << l << " right: " << r << endl;
			//ES[i][j].push_back(l);//i表示第几个组，j表示第几行
			//ES[i][j].push_back(r);
			j++;

			//for (int b = 0; b < ES[i][j].size(); b++) {
			//	data[j][b] = ES[i][j][b];
			//	cout << data[j][b] << endl;
			//	cout << "get  data" << endl;
			//}//end for
			//cout << "get  data" << endl;
			//cout << ES[i][j].size() << endl;
			//cout << ES[0][0][2] << endl;
		}
		PerCluster_Num[i] = j;
		//printf("%d\n", PerCluster_Num[i]);
		All_Position[i].erase(All_Position[i].begin() + j, All_Position[i].end());
		ifs.close();





	}
	return All_Position;
}


	//for (int i = 0; i < 39; i++)
	//{
	//	for(int j = 0;j<5;j++)
	//	{
	//		for (int h = 0; h < 3; h++)
	//		{
	//			cout << All_Position[i][j][h] << endl;
	//		}
	//	}
	//}

