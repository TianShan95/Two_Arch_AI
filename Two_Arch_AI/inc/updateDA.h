#pragma once


using namespace std;
#include <vector>

int updateDA(vector<vector<vector<vector<double>>>>&CPOP, \
	vector<vector<vector<vector<double>>>>&DA, \
	vector<vector<double> >&cobj, vector<vector<double> >&DAobj);

int DAselect(vector<vector<vector<vector<double>>>>&NDA, vector<vector<vector<vector<double>>>>&NDAobj, \
	vector<vector<vector<vector<double>>>>&DA, vector<vector<vector<vector<double>>>>&DAobj);

