#ifndef WhaaleContinuousEstimate_H
#define WhaaleContinuousEstimate_H

#include"Sample.h"

class WhaaleContinuousEstimate
{
	private:
		vector<double> T;

		double a(double t, int n)
		{
			//return exp(-n);
			return 1;
		}

		double V(double t)
		{
			if( t < 0 )
				return 1.0 - 0.5*exp( t );
			else
				return 0.5*exp( -t );
		}

	public:
		WhaaleContinuousEstimate(Sample &S)
		{
			T.clear();
			T = S.GetSample();
			sort(T.begin(),T.end());
		}

		double Probability(double x)
		{
			double P = 0.0;
			for(int i=0; i<T.size(); i++)
				P += V( x-T[i]/a(x,i) )/double( T.size() );
			return P;
		}

		double Quantile(double alpha)
		{
		}

		char *getEstimateTitle()
		{
			return "WhaaleContinuousEstimate";
		}
};

#endif