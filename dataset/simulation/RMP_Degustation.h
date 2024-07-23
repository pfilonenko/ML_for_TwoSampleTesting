#ifndef RMP_Degustation_H
#define RMP_Degustation_H

#include"Sample.h"

class RMP_Degustation
{
	int N;
	EDF *F;
	double Mean, Var;

	private:
		double Score(int num)
		{
			switch(num)
			{
				case 1:
					return 10.4;
					break;
				case 2:
					return 39.4;
					break;
				case 3:
					return 53.6;
					break;
				case 4:
					return 62.8;
					break;
				case 5:
					return 69.2;
					break;

				case 6:
					return 74.2;
					break;
				case 7:
					return 78.4;
					break;
				case 8:
					return 81.6;
					break;
				case 9:
					return 84.6;
					break;
				case 10:
					return 87.0;
					break;

				case 11:
					return 89.4;
					break;
				case 12:
					return 91.4;
					break;
				case 13:
					return 93.4;
					break;
				case 14:
					return 95.6;
					break;
				case 15:
					return 100.0;
					break;
			}
		}

		void Initializing()
		{
			vector<double> mas;
			for(int i=1; i<=15; i++)
			{
				double sc = Score(i);
				for(int j=0; j<sc; j++)
					mas.push_back( sc );
			}
			F = new EDF(mas);
		}

		double Statistic()
		{
			double S;
			vector<double> Sc(5,0);
			for(int j=0; j<Sc.size(); j++)
			{
				vector<double> mas;

				for(int i=0; i<N; i++)
				{
					double p = GwMT19937[0].MT19937Uniform01();
					mas.push_back( F->Quantile(p) );
				}
				
				Sc[j] = Sample(mas).Median();
			}
			S = 0.08*(Sc[0]+Sc[1]) + 0.28*(Sc[2]+Sc[3]+Sc[4]);

			return S;
		}

	public:
		RMP_Degustation(int n)
		{
			this->N = n;
			Initializing();

			int MonteCarloSize = 30000;
			vector<double> Stat;
			for(int i=0; i<MonteCarloSize; i++)
			{
				double val = Statistic();
				Stat.push_back( val );
			}
			Sample ResS(Stat);
			
			char buf[512];
			sprintf(buf,"G(S.H0)_n=%d.dat",N);
			ResS.Save(buf);

			Mean = ResS.Mean();
			Var = ResS.UnshiftedVariance();
		}

		~RMP_Degustation()
		{
			//delete [] F;
		}

		double GetMean()
		{
			return Mean;
		}

		double GetVariance()
		{
			return Var;
		}
};

#endif