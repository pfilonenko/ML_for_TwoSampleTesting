#ifndef ConvergenceToLimitLaw_H
#define ConvergenceToLimitLaw_H

#include<omp.h>
#include<vector>
#include"MP.h"
#include"AlternativeHypotheses.h"
using namespace std;

class ConvergenceToLimitLaw
{
	protected:
		vector<vector<double>> nDn;	//n and distance Dn

		virtual double F(double x)=0;
		virtual double CalculateStatistic(Sample &A, Sample &B)=0;
		
		double KolmogorovDistance(vector<double> &Mas)
		{
			int N = Mas.size();
			double d1,d2,func,Dn;		//d1 - max D-
										//d2 - max D+
										//func - value at the mas[i]
			sort(Mas.begin(),Mas.end());

			vector<double> maxd( N );
			omp_set_num_threads( omp_get_max_threads() );

			Dn = d1 = d2 = -DBL_MAX;
			
			#pragma omp parallel for
			for(int i=0; i<N; i++)
			{
				func = F(Mas[i]);
				d1 = double(i+1)/double(N) - func;
				d2 = func - double(i)/double(N);

				maxd[i] = max(d1,d2);
			}

			for(int i=0; i<maxd.size(); i++)
				if( maxd[i] > Dn )
					Dn = maxd[i];

			return Dn;
		}

	public:
		vector<vector<double>> Convergence(vector<MP_HT> &mp)
		{
			int kol = mp.size();
			if( !kol )
			{
				vector<vector<double>> nullv;
				return nullv;
			}
			
			// we go by sample sizes
			for(int r=0; r<kol; r++)
			{
					double value;
					int N = mp[r].MonteKarloSize;
					int NumThreads = mp[r].NumThreads;

					vector<double> Statistic( N );

					AlternativeHypotheses At1_1(mp[r].H,mp[r].num0,0),At1_2( mp[r].H, mp[r].num0, mp[r].Percent0 );
					AlternativeHypotheses At2_1(mp[r].H,mp[r].num1,0),At2_2( mp[r].H, mp[r].num1, mp[r].Percent1 );

					nDn.resize( 2 );
					nDn[0].resize( kol );
					nDn[1].resize( kol );
        
					omp_set_num_threads( NumThreads );

					vector<int> dim( NumThreads, N/NumThreads );
					int ost = N%NumThreads;
					for(int i=0; ost>0; i++)
					{
						dim[i]++;
						ost--;
					}

					int n1 = mp[r].n1;
					int n2 = mp[r].n1;

					clock_t tp;
					tp = clock();

					#pragma omp parallel
					{
						int rank = omp_get_thread_num();
				
						int beg = 0,end;
						for(int i=0; i<rank; i++)
							beg += dim[i];
						end = beg + dim[rank];

						auto& D1 = *At1_1.D;
						auto& D2 = *At2_1.D;

						for(int i=beg; i<end; i++)
						{
							if( clock() > tp + 1000 && rank==0 )
							{
								printf("%.2lf\r",double(i-beg)/double(end-beg)*100.0);
								tp = clock();
							}
rep:
							// simulated samples
							Sample A(D1,mp[r].n1,GwMT19937[rank]);
							Sample B(D2,mp[r].n2,GwMT19937[rank]);

							// censoring the sample
							if( mp[r].Percent0>0 )
								A.CensoredTypeThird( *At1_2.D, GwMT19937[rank]);
							if( mp[r].Percent1>0 )
								B.CensoredTypeThird( *At2_2.D, GwMT19937[rank]);

							// calculated the value of statistics
							value = CalculateStatistic(A, B);
							if( value==value )
								Statistic[i] = value;
							else
								goto rep;
						}
					}
					printf("Complete.\n");

					// calculate the distance between distributions using Kolmogorov statistics
					nDn[0][r] = (n1+n2)/2;
					nDn[1][r] = KolmogorovDistance(Statistic);
					printf("D[%.0lf] = %lf\n\n",nDn[0][r],nDn[1][r]);

					// cleaned the distribution of test statistics
					Statistic.clear();
			}
			return nDn;
		}
};

#endif
