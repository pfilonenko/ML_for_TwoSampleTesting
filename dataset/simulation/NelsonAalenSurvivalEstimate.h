// nonparametric estimate of the survival function S(t) 
// using the Nelson-Aalen intensity accumulation function estimate

#ifndef NelsonAalenSurvivalEstimate_H
#define NelsonAalenSurvivalEstimate_H

#include<vector>
#include"Sample.h"
using namespace std;

class NelsonAalenSurvivalEstimate
{
	private:
		vector<double> X;	// times
		vector<double> F;	// probabilities
		bool CensoredLast;	// flag whether the last value is censored

	public:
		NelsonAalenSurvivalEstimate(Sample &s);
		~NelsonAalenSurvivalEstimate();

		double Probability(double t);
		double Quantile(double p);
		char *getEstimateTitle();
};


#endif