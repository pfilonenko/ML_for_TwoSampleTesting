#ifndef MP_HT_H
#define MP_HT_H

#include<omp.h>
#include<vector>
using namespace std;

//ModelingParameters ~ MP
class MP_HT
{
	public:
		MP_HT()
		{
			this->Percent0 = 0;
			this->Percent1 = 0;

			this->NumThreads = omp_get_max_threads();

			this->TypeCensored = 3;

			this->num0 = 1;
			this->num1 = 2;

			this->MonteKarloSize = 16600;

			this->Alpha = 0.05;
			this->Power = 0.75;
			this->Repeat = 5;

			this->SimulationType = 1;
		}

		void Set(
				int n1, int n2, 
				int H = 1,		
				int num0 = 1,	int Percent0 = 0,  
				int num1 = 1,	int Percent1 = 0, 
				int NumThreads = 8, int MonteKarloSize = 16600, 
				double _alpha = 0.05, double _1_beta = 0.75, 
				int Repeat = 1, 
				int TypeCensored = 3
			)
		{
			this->n1 = n1;
			this->n2 = n2;

			this->H = H;

			this->num0 = num0;
			this->Percent0 = Percent0;

			this->num1 = num1;
			this->Percent1 = Percent1;
			
			this->NumThreads = NumThreads;
			this->MonteKarloSize = MonteKarloSize;
			
			this->Alpha = _alpha;
			this->Power = _1_beta;
			this->Repeat = Repeat;

			this->TypeCensored = TypeCensored;
		}

		bool operator <(MP_HT &A)
		{
			if( this->n1+this->n2 < A.n1+A.n2 )
				return true;
			else
				return false;
		}

		int n1, n2;				// sample sizes

		int H;

		int num0;
		int Percent0;		// degree of censoring

		int num1;
		int Percent1;		// degree of censoring

		int NumThreads;		// number of threads
		int MonteKarloSize;	// sample size statistics

		double Alpha;	// Type I error
		double Power;	// 1 - Type II error (Test Power)
		int Repeat;		// number of repetitions when calculating power

		int SimulationType;	// how to model a distribution (1 - Monte Carlo, 2 - Bootstrap, 3 - Pseudocomplete sampling)

		int TypeCensored;	// Censoring Type (1, 2 or 3)
};

#endif
