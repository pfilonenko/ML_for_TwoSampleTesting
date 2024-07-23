#ifndef KAPLANMEYEReSTIMATE_H
#define KAPLANMEYEReSTIMATE_H

#include<vector>
#include"Sample.h"
using namespace std;

class KaplanMeyerEstimate
{
	private:
		vector<double> X,F;
		bool TheLastIsCensoredObservation;

	public:
		KaplanMeyerEstimate(Sample &S)
		{
			X.resize( S.N() );
			F.resize( S.N() );

			S.SortSample();

			if( S._C( S.N()-1 )==1 )
				TheLastIsCensoredObservation = true;
			else
				TheLastIsCensoredObservation = false;

			double val = 1.0;
			for(int i=0; i<X.size(); i++)
			{
				X[i] = S._X(i);

				if( S._C(i)==0 )
				{
					F[i] = val*( double( X.size()-(i+1) )/double( X.size()-(i+1)+1 ) );
					val = F[i];
				}
				else
					F[i] = val;
			}

			for(int i=X.size()-1; i>0; i--)
				F[i] = F[i-1];
			F[0] = 1.0;
		}

		double Probability(double x)
		{
			if( x < X[0] )	//before
				return F[0];
			else
			{
				if( x >= X[X.size()-1] )	//after
				{
					if( TheLastIsCensoredObservation==false )
						return 0.0;
					else
						return F[F.size()-1];
				}
				else
				{
					//into
					for(int i=0; true; i++)
						if( x>=X[i] && x<X[i+1] )
							return F[i+1];
				}
			}
		}

		double Quantile(double alpha)
		{
			if( alpha >= 1.0 )
				return -DBL_MAX;
			else
			{
				if( alpha <= 0.0 )
					return DBL_MAX;
				else
				{
					if( alpha < F[F.size()-1] )
						if( TheLastIsCensoredObservation==true )
							return DBL_MAX;
						else
							return X[X.size()-1];
					else
						for(int i=0; true; i++)
							if( alpha < F[i] && alpha >= F[i+1] )
								return X[i];
				}
			}

		}

		char *getEstimateTitle()
		{
			return "KaplanMeyerEstimate";
		}
};

#endif