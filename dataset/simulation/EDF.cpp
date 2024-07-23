#include"EDF.h"

// Quantile calculation, quantiles are not reversed
double EDF::Quantile(double alpha)
{
	if( alpha >= 1.0 || alpha <= 0.0 )
		return DBL_MAX;
	else
		return Edf[ int(alpha*Edf.size()) ];
}

double EDF::Probability(double x)
{
	double res = 0.0;
	if( x < Edf[0] )
		return 0.0;
	else
		if( x >= Edf[Edf.size()-1] )
			return 1.0;
		else
			for(int i=Edf.size()-2; i>-1; i--)
				if( Edf[i]<=x && x<Edf[i+1] )
					return double(i+1)/double(Edf.size());
}

EDF::EDF(vector<double> &mas)
{
	Edf = mas;
	std::sort(Edf.begin(),Edf.end());
}