#ifndef POWER_H
#define POWER_H

#include<omp.h>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

class Power
{
	private:
		vector<double> H0;
		vector<double> H1;

		char TypeOfHypothesys[512];	//type of critical area (left-sided, right-sided, two-sided)

	public:
		Power(vector<double> &h0, vector<double> &h1, const char type[]);
		Power(char *fn0, char *fn1, const char type[]);

		double Value(double alpha);
};

#endif