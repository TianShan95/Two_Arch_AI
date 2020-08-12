#include "Caculate_Distance.h"

/* p1 express the position data include latitude and longitude */
double Caculate_Real_Distance(vector<double> p1, vector<double> p2)  
{
	double dlon, dlat;  // dlon express the longitude differece of the two position, so does dlat
	double a, c, r;  // express a parameter of caculate real distance

	/* Use s1[] for converting from degree to radian */
	double s1[4];
	s1[0] = (p1[0] * M_PI) / 180;
	s1[1] = (p1[1] * M_PI) / 180;
	s1[2] = (p2[0] * M_PI) / 180;
	s1[3] = (p2[1] * M_PI) / 180;
	
	dlat = s1[0] - s1[2];  // latitude difference between p1 and p2
	//printf("dlat: %f \n ", dlat);
	dlon = s1[1] - s1[3];  // longitude difference between p1 and p2
	//printf("dlon: %f \n", dlon);
	a = pow(sin(dlat / 2), 2) + cos(s1[0])*cos(s1[2])*pow(sin(dlon / 2), 2);
	c = 2 * atan2(sqrt(a), sqrt(1 - a));
	r = 6371000;  // the radius of earth
	return c * r;  // return the real distance of two positions
}

/* p1 express the position data include latitude and longitude */
double Caculate_O_Distance(vector<double> p1, vector<double> p2)
{
	double dlon, dlat;  // dlon express the longitude differece of the two position, so does dlat
	double O_distance;  // express a parameter of caculate real distance

	/* Use s1[] for converting from degree to radian */
	double s2[4];
	s2[0] = p1[0];  // latitude
	s2[1] = p1[1];  //longitude
	s2[2] = p2[0];
	s2[3] = p2[1];

	dlat = s2[0] - s2[2];  // latitude difference between p1 and p2
	//printf("dlat: %f \n ", dlat);
	dlon = s2[1] - s2[3];  // longitude difference between p1 and p2
	//printf("dlon: %f \n", dlon);
	O_distance = sqrt(pow(dlat, 2) + pow(dlon, 2));
	return O_distance;  // return the real distance of two positions
}