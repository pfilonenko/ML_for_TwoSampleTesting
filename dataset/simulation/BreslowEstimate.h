//paper: А.А. Абдушукурова и Р.С. Мурадова (2013) "Об оценках функции распределения в моделях случайного цензурирования"
#ifndef BreslowEstimate_H
#define BreslowEstimate_H

#include<vector>
#include<math.h>
#include"Sample.h"
using namespace std;

class BreslowEstimate
{
	private:
		vector<double> X,F;

	public:
		BreslowEstimate(Sample &S)
		{
			S.SortSample();

			X.resize( S.N() );
			F.resize( S.N() );

			double sum = 0.0;
			for(int i=0; i<X.size(); i++)
			{
				X[i] = S._X(i);

				double val = 0;
				if( S._C(i)==0 )
				{
					val = 1.0/double( S.N()-(i+1)+1 );
				}
				sum += val;

				F[i] = exp( -sum );

			}

		}

		double Probability(double x)
		{
			double p;
			if( x < this->X[0] )
				p = 1.0;
			else
				if( x >= this->X[ X.size()-1 ] )
					p = F[ F.size()-1 ];
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
			if( alpha < F[ F.size()-1 ] )
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
			return "BreslowEstimate";
		}
};

#endif
