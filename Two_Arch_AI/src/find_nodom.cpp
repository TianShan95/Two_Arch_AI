#include"Init.h"


vector<vector<vector<vector<double>>>> find_nodom_ai(vector<vector<vector<vector<double>>>>&POP, \
												  vector<vector<double>>&obj, \
												  vector<vector<double>>&DAobj, int m)
{
	int i, j; i = 0;
	int z;
	int k;
	vector<vector<vector<vector<double>>>> DA(POP);  // ����һ����Ⱥ������DA
	//vector<double> a(c + m), b(c + m);
	vector<double>a(m), b(m); // ����Ŀ������
	while (i < DA.size())  // ��ѯDA�����е��࣬����while��Ƕ����Ϊ��ʵ��DA�����е���Ⱥ�������Աȣ������ŵ���Ⱥ���£�����������
	{
		int flag = 0;
		j = i + 1;
		a = DAobj[i];  // �ѵ�(i+1)�εõ���Ŀ��ֵ��a
		while (j < DA.size())  // ��ѯDA�����е���Ⱥ���ӵڶ�����Ⱥ��ʼ�����whileΪ�˹̶�סa��Ŀ��ֵ��������Ŀ��ֵ����a�ֶԱ�
		{
			b = DAobj[j];  // �ѵ�(j+1)�εõ���Ŀ��ֵ��b����һ�ε�whileѭ����b����a�ֵ���һ��
			z = dom(a, b, m);  // �����βΣ��ֱ���ĳһ�ֵ�Ŀ��ֵa��ĳһ�ֵ�Ŀ��ֵb����a����b��֮ǰ����Ŀ�����m���ж�a��һ�ֺ�b��һ��Ŀ��ֵ����ͬ
			if (z == 2)  // a�ֵ�Ŀ��ֵȫ������b�ֵ�Ŀ��ֵ
			{
				flag = 1;
				break;
			}
			else if (z == 3)  // a�ֵ�Ŀ��ֵȫ������b�ֵ�Ŀ��ֵ
			{
				DA.erase(DA.begin() + j);
				DAobj.erase(DAobj.begin() + j);  // ������һ�ε�DA���������Դ浵

			}
			else if (z == 1)  // a�ֵ�Ŀ��ֵȫ��С��b�ֵ�Ŀ��ֵ
			{
				DAobj.erase(DAobj.begin() + j);
				DA.erase(DA.begin() + j);   // ������һ�ε�DA�����Դ浵��a�ֵĸ�С�����԰�b�ֵĲ�������j��b�ֵ��±�

			}
			else  // a�ֵ�Ŀ��ֵ��b�ֵ�Ŀ��ֵ��������ϵ
			{
				j++;
			}
		}
		if (flag == 1)  //while����a�ֱ���̭����������aҲ��DA�в���
		{
			DA.erase(DA.begin() + i);
			DAobj.erase(DAobj.begin() + i);

		}
		else // ���򻻹̶���һ��i
		{
			i++;
		}
	}
	return DA;//���ǰ���ε�n�ֵĽ��������ŵ��Ǹ���Ⱥ����������
}