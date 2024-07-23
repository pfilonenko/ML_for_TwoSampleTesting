#ifndef StatisticsSample_H
#define StatisticsSample_H

#include<omp.h>
#include"MP.h"
#include"AlternativeHypotheses.h"
#include"KaplanMeyerEstimate.h"
#include"ContinuousSurvivalEstimate.h"

class StatisticsSample
{
	private:
		//generate a vector of dimensions for each thread
		vector<int> GetDimensions(int CountThreads, int MonteKarloSize)
		{
			unsigned i, kol;
			vector<int> dim( CountThreads );

			kol = MonteKarloSize/CountThreads;
			for(i=0; i<CountThreads; i++)
				dim[i] = kol;

			kol = MonteKarloSize - CountThreads*kol;	// how much is left after non-integer division?
			for(i=0; kol>0; i++,kol--)
				dim[i]++;

			return dim;
		}

		// procedure for obtaining a pseudo-complete sample
		Sample PseudoCompleSampling(Sample &S, int rank)
		{
			vector<double> newv;
			ContinuousSurvivalEstimate F(S);

			for(int i=0; i<S.N(); i++)
			{
				if( S._C(i)==1 )
				{
					double p = F.Probability( S._X(i) );
					double a = p*GwMT19937[rank].MT19937Uniform01();
					newv.push_back( F.Quantile( a ) );
				}
				else
					newv.push_back( S._X(i) );
			}
			Sample Pseudo(newv);
			return Pseudo;
		}

	protected:
		virtual double CalculateStatistic(Sample &A, Sample &B)=0;
		virtual void TitleTest(char title[])=0;

		// modeling the distribution of statistics using Monte Carlo
		vector<double> Modelling(MP_HT &mp)
		{
			// we take the sample distribution and its censoring distribution for type 3 censoring
			AlternativeHypotheses F1(mp.H,mp.num0,0), F2(mp.H,mp.num1,0);

			omp_set_num_threads( mp.NumThreads );

			vector<int> dim = GetDimensions(mp.NumThreads,mp.MonteKarloSize);

			clock_t tp;
			tp = clock();

			vector<double> S;
			S.resize( mp.MonteKarloSize );
			#pragma omp parallel
			{
				int i,beg,end;
				int rank = omp_get_thread_num();

				beg = end = 0;
				for(i=0; i<rank; i++)
					beg += dim[i];
				end = beg + dim[rank];

				auto& D1 = *F1.D;
				auto& D2 = *F2.D;

				for(int i=beg; i<end; i++)
				{
					if( clock() > tp + 1000 && rank==0 )
					{
						printf("%.2lf\r",double(i-beg)/double(end-beg)*100.0);
						tp = clock();
					}

					Sample A(D1,mp.n1,GwMT19937[rank]);
					Sample B(D2,mp.n2,GwMT19937[rank]);

					// censoring the sample
					switch( mp.TypeCensored )
					{
						case 1:
							break;
						case 2:
							if( mp.Percent0 > 0 )
								A.CensoredTypeSecond(mp.Percent0);
							if( mp.Percent1 > 0 )
								B.CensoredTypeSecond(mp.Percent1);
							break;
						case 3:
							if( mp.Percent0 > 0 )
							{
								AlternativeHypotheses FC( mp.H, mp.num0, mp.Percent0 );
								A.CensoredTypeThird( *FC.D, GwMT19937[rank]);
							}
							if( mp.Percent1 > 0 )
							{
								AlternativeHypotheses FC( mp.H, mp.num1, mp.Percent1 );
								B.CensoredTypeThird( *FC.D, GwMT19937[rank]);
							}
							break;
					}
					
					S[i] = CalculateStatistic(A,B);
				}
			}
			printf("Complete.\n");

			return S;
		}

		// we pass the modeling parameters, we get the distribution
		vector<double> ModellingBootstrap(MP_HT &mp)
		{
			// we take the sample distribution and its censoring distribution for type 3 censoring
			AlternativeHypotheses F1(mp.H,mp.num0,0), F2(mp.H,mp.num1,0);

			auto& D1 = *F1.D;
			auto& D2 = *F2.D;

			Sample A(D1,mp.n1,GwMT19937[0]);
			Sample B(D2,mp.n2,GwMT19937[0]);

			// censoring the sample
			switch( mp.TypeCensored )
			{
				case 1:
					break;
				case 2:
					if( mp.Percent0 > 0 )
						A.CensoredTypeSecond(mp.Percent0);
					if( mp.Percent1 > 0 )
						B.CensoredTypeSecond(mp.Percent1);
					break;
				case 3:
					if( mp.Percent0 > 0 )
					{
						AlternativeHypotheses FC( mp.H, mp.num0, mp.Percent0 );
						A.CensoredTypeThird( *FC.D, GwMT19937[0]);
					}
					if( mp.Percent1 > 0 )
					{
						AlternativeHypotheses FC( mp.H, mp.num1, mp.Percent1 );
						B.CensoredTypeThird( *FC.D, GwMT19937[0]);
					}
					break;
			}

			return Bootstrap(A,B,mp.MonteKarloSize);
		}

		// modeling the distribution of statistics using pseudo-complete samples
		vector<double> ModellingPseudo(MP_HT &mp)
		{
			// we take the sample distribution and its censoring distribution for type 3 censoring
			AlternativeHypotheses F1(mp.H,mp.num0,0), F2(mp.H,mp.num1,0);

			omp_set_num_threads( mp.NumThreads );

			vector<int> dim = GetDimensions(mp.NumThreads,mp.MonteKarloSize);

			clock_t tp;
			tp = clock();

			vector<double> Sn;
			Sn.resize( mp.MonteKarloSize );
			#pragma omp parallel
			{
				int i,beg,end;
				int rank = omp_get_thread_num();

				beg = end = 0;
				for(i=0; i<rank; i++)
					beg += dim[i];
				end = beg + dim[rank];

				auto& D1 = *F1.D;
				auto& D2 = *F2.D;

				for(int i=beg; i<end; i++)
				{
					if( clock() > tp + 1000 && rank==0 )
					{
						printf("%.2lf\r",double(i-beg)/double(end-beg)*100.0);
						tp = clock();
					}

					Sample A(D1,mp.n1,GwMT19937[rank]);
					Sample B(D2,mp.n2,GwMT19937[rank]);

					// censoring the sample
					switch( mp.TypeCensored )
					{
						case 1:
							break;
						case 2:
							if( mp.Percent0 > 0 )
								A.CensoredTypeSecond(mp.Percent0);
							if( mp.Percent1 > 0 )
								B.CensoredTypeSecond(mp.Percent1);
							break;
						case 3:
							if( mp.Percent0 > 0 )
							{
								AlternativeHypotheses FC( mp.H, mp.num0, mp.Percent0 );
								A.CensoredTypeThird( *FC.D, GwMT19937[rank]);
							}
							if( mp.Percent1 > 0 )
							{
								AlternativeHypotheses FC( mp.H, mp.num1, mp.Percent1 );
								B.CensoredTypeThird( *FC.D, GwMT19937[rank]);
							}
							break;
					}

					A = PseudoCompleSampling(A, rank);
					B = PseudoCompleSampling(B, rank);
					
					Sn[i] = CalculateStatistic(A,B);
				}
			}
			printf("Complete.\n");

			return Sn;
		}

	public:
		vector<double> SampleStatistics(MP_HT &mp)
		{
			if( mp.SimulationType == 1 )
				return Modelling(mp);
			else
				if( mp.SimulationType == 2 )
					return ModellingBootstrap(mp);
				else
					return ModellingPseudo(mp);
		}

		vector<double> Bootstrap(Sample &A, Sample &B, int MonteKarloSize=16600)
		{
			//var-result
			vector<double> S( MonteKarloSize );

			vector<double> ms;
			vector<int> cs;
			for(int i=0; i<max(A.N(),B.N()); i++){
				if( i<A.N() ){
					ms.push_back( A._X(i) );
					cs.push_back( A._C(i) );
				}

				if( i<B.N() ){
					ms.push_back( B._X(i) );
					cs.push_back( B._C(i) );
				}
			}
			Sample Union(ms,cs);
			ContinuousSurvivalEstimate F(Union);
			ContinuousSurvivalEstimate F1(A),F2(B);

			clock_t tp;
			tp = clock();
			int num;

			#pragma omp parallel for
			for(int i=0; i<MonteKarloSize; i++)
			{
				int rank = omp_get_thread_num();

				//common output in command-line
				if( clock() > tp + 1000 && rank==0 )
				{
					printf("%.2lf\r",double(i)/double(MonteKarloSize)*100.0);
					tp = clock();
				}

				vector<double> x;
				for(int j=0; j<A.N(); j++)
					x.push_back( F.Quantile( GwMT19937[rank].MT19937Uniform01() ) );
				Sample S1(x);
				x.clear();
				
				for(int j=0; j<B.N(); j++)
					x.push_back( F.Quantile( GwMT19937[rank].MT19937Uniform01() ) );
				Sample S2(x);

				S[i] = this->CalculateStatistic(S1,S2);
			}
			printf("Complete.\n");

			return S;
		}
};

#endif
