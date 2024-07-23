// Empirical distribution function

#ifndef EDF_H
#define EDF_H

#include<vector>
#include<algorithm>
using namespace std;

class EDF
{
	private:
		vector<double> Edf;

	public:
		EDF(vector<double> &mas);

		double Quantile(double alpha);
		double Probability(double x);
};

#endif