#ifndef TestPower_H
#define TestPower_H

#include"Power.h"
#include"StatisticsSample.h"

// structure, stores dimension, power as mathematical expectation, power dispersion for the number of repeats
struct SizePowerVariance
{
	int H;		// alternative hypothesis
	int Per1;	// degree of censoring
	int Per2;	// degree of censoring
	
	int n1;	// sample size
	int n2;	// sample size

	double Power;
	double Var;

	// power confidence interval
	double LeftPower,RightPower;
};

class TestPower:
	public StatisticsSample
{
	private:
		// calculation of expected power
		double Mean(vector<double> &S)
		{
			double res = 0;
			for(int i=0; i<S.size(); i++)
				res += S[i];
			res /= double(S.size());
			return res;
		}

		// power dispersion calculation
		double Variance(vector<double> &S)
		{
			double res = 0;
			double mean = Mean(S);
			for(int i=0; i<S.size(); i++)
				res += pow( S[i] - mean, 2 );
			res /= double(S.size()-1);
			return res;
		}

	protected:
		virtual string TestType()=0;

	public:
		vector<SizePowerVariance> CalculatePower(vector<MP_HT> &mp)
		{
			vector<SizePowerVariance> SPV;

			//name of test
			char buf[512];
			this->TitleTest(buf);

			for(int r=0; r<mp.size();r++)
			{
				int N = mp[r].MonteKarloSize;
				int NumThreads = mp[r].NumThreads;

				printf("%s H%d per:%d n=%d\n",buf,mp[r].H,mp[r].Percent0,mp[r].n1);

					vector<double> power( mp[r].Repeat );
					for(int i=0; i<mp[r].Repeat; i++)
					{
						MP_HT _h0,_h1;
						_h0.Set(mp[r].n1,mp[r].n2,mp[r].H,mp[r].num0,mp[r].Percent0,mp[r].num0,mp[r].Percent0,NumThreads,N,mp[r].Alpha,mp[r].Power,mp[r].Repeat,mp[r].TypeCensored);
						_h1.Set(mp[r].n1,mp[r].n2,mp[r].H,mp[r].num0,mp[r].Percent0,mp[r].num1,mp[r].Percent1,NumThreads,N,mp[r].Alpha,mp[r].Power,mp[r].Repeat,mp[r].TypeCensored);

						_h0.SimulationType = mp[r].SimulationType;
						_h1.SimulationType = mp[r].SimulationType;

						auto H0 = SampleStatistics( _h0 );
						auto H1 = SampleStatistics( _h1 );

						Power P(H0,H1,TestType().c_str());
						power[i] = P.Value( mp[r].Alpha );
					}

					//Make file
					SizePowerVariance res;
					res.H = mp[r].H;
					res.Per1 = mp[r].Percent0;
					res.Per2 = mp[r].Percent1;
					res.n1 = mp[r].n1;	// sample size
					res.n2 = mp[r].n2;	// sample size
					if( mp[r].Repeat>1 )
					{
						res.Power = Mean(power);	// test power
						res.Var = Variance(power);	// variance

						cout << res.Power << endl << endl;

						double a = 0.99;				// confidence probability
						CRVStudent tSt(mp[r].Repeat-1);

						double t = tSt.Quantile( (1-a)/2.0 );
						res.LeftPower	= res.Power + t*sqrt( res.Var/double(mp[r].Repeat) );
						res.RightPower	= res.Power - t*sqrt( res.Var/double(mp[r].Repeat) );
					}
					else
					{
						res.Power = res.LeftPower = res.RightPower = power[0];
						res.Var = 0.00;
						cout << res.Power << endl << endl;
					}

					SPV.push_back( res );
			}
			
			return SPV;
		}
};

#endif
