//paper: А.А. Абдушукурова и Р.С. Мурадова (2013) "Об оценках функции распределения в моделях случайного цензурирования"
#ifndef AdbushukurovEstimate_H
#define AdbushukurovEstimate_H

#include<vector>
#include"Sample.h"
#include"NelsonAalenSurvivalEstimate.h"
#include"BreslowEstimate.h"
using namespace std;

class AbdushukurovEstimate
{
	private:
		vector<double> X,F;
		BreslowEstimate *FB;

		double R(double t, Sample &S)
		{
			double res = 0;
			for(int j=0; j<S.N(); j++)
			{
				if( S._X(j)<=t )
					res += 1.0/double( S.N()-(j+1)+1 );
			}
			return -log( FB->Probability(t) )/res;
		}

	public:
		AbdushukurovEstimate(Sample &S)
		{
			S.SortSample();
			
			X.resize( S.N() );
			F.resize( S.N() );

			FB = new BreslowEstimate(S);

			for(int i = 0; i<S.N(); i++)
			{
				X[i] = S._X(i);
				F[i] = pow( double(S.N()-(i+1))/double(S.N()), R( X[i], S) );
			}
		}

		double Probability(double x)
		{
			double p;
			if( x < this->X[0] )
				p = 1.0;
			else
				if( x >= this->X[ X.size()-1 ] )
					p = 0.0;
				else
				{
					for(int i=0; X.size()-1; i++)
					{
						if( x >= X[i] && x < X[i+1] )
						{
							p = F[i];
							break;
						}
					}
				}
			return p;
		}

		double Quantile(double alpha)
		{
			double res;
			if( alpha <= DBL_EPSILON )
				res = DBL_MAX;
			else
				if( alpha >= 1.0 )
					res = -DBL_MAX;
				else
				{
					double a,b;
					a = 1.0; b = F[0];
					for(int i=0; i<F.size(); i++)
					{
						if( alpha < a && alpha >= b )
						{
							res = X[i];
							break;
						}

						a = b;
						b = F[i+1];
					}
				}
			return res;
		}

		char *getEstimateTitle()
		{
			return "AdbushukurovEstimate";
		}

		~AbdushukurovEstimate()
		{
			delete FB;
		}
};

#endif