
/* ����Ӧ���Ƕ�����ֵ����ĳ��������������ֵ�Ƚ� */
/*vector<vector<double > > Boundary_init(int c)
{
	vector<vector<double > > BD(2);
	BD[0].resize(c);
	BD[1].resize(c);
	for (int j = 0;j<c;j++)
	{
		BD[0][j] = 1.0;
		BD[1][j] = 0.0;
	}
	return BD;
}*/
double **Boundary_init(int c)
{
	double **BD = new double*[2];
	BD[0] = new double[c], BD[1] = new double[c];
	for (int j = 0; j < c; j++)
	{
		BD[0][j] = 1.0;
		BD[1][j] = 0.0;
	}
	return BD;
}