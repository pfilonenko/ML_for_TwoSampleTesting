#ifndef SearchN_H
#define SearchN_H

#include"TestPower.h"

struct sScan
{
	int n;
	double p;

	bool operator <(sScan &A)
	{
		if( n < A.n )
			return true;
		else
			return false;
	}
};

class SearchN : public TestPower
{
	private:
		double mdPower(MP_HT &mp)
		{
			int k = mp.NumThreads;
			int N = mp.MonteKarloSize;

			MP_HT _h0,_h1;
			_h0.Set(mp.n1,mp.n2,mp.H,mp.num0,mp.Percent0,mp.num0,mp.Percent0,k,N,mp.Alpha,mp.Power,mp.Repeat,mp.TypeCensored);
			_h1.Set(mp.n1,mp.n2,mp.H,mp.num0,mp.Percent0,mp.num1,mp.Percent1,k,N,mp.Alpha,mp.Power,mp.Repeat,mp.TypeCensored);

			auto H0 = SampleStatistics( _h0 );
			auto H1 = SampleStatistics( _h1 );

			Power P(H0,H1,this->TestType().c_str());

			return P.Value( mp.Alpha );
		}

	public:
		vector<sScan> Scanner(MP_HT &mp)
		{
			MP_HT mpt;
			sScan temp;
			vector<sScan> res;
			double powerL, powerN;	//power last, power next

			char title[512];
			this->TitleTest(title);
			printf("%s\tH%d\n",title,mp.H);

			int n = 4;
			mpt = mp; mpt.n1 = mpt.n2 = n;
			powerN = mdPower( mpt );
			printf("Power(%lf; %d)=%lf\n\n",mp.Alpha,n,powerN);

			temp.n = n;
			temp.p = powerN;
			res.push_back( temp );

			bool P = true;
			while( true )
			{
				n *= 2;
				if( n > 5000 )
				{
					P = false;
					break;
				}

				powerL = powerN;

				mpt = mp; mpt.n1 = mpt.n2 = n;
				powerN = mdPower( mpt );
				printf("Power(%d)=%lf\tPower(%d)=%lf\n\n",n/2,powerL,n,powerN);

				temp.n = n;
				temp.p = powerN;
				res.push_back( temp );

				if( powerN > mp.Power+0.02 )
					break;
			}

			if( P==true )
			{
				int a,c,b;
				double pa,pb;
				a = n/2;
				b = n;

				pa = res[res.size()-2].p;
				pb = res[res.size()-1].p;

				while( true )
				{
					c = (a+b)/2;
					if( c==a || c==b )
						break;

					mpt = mp; mpt.n1 = mpt.n2 = c;
					double p = mdPower( mpt );
		
					sScan rt;
					rt.n = c;
					rt.p = p;
					res.push_back( rt );

					printf("P(%d) = %lf\tP(%d) = %lf\tP(%d) = %lf\n\n",a,pa,c,p,b,pb);

					//if( fabs(mp.Power-p)<0.005 )
					//	break;

					if( mp.Power < p )
					{
						b = c;
						pb = p;
					}
					else
					{
						a = c;
						pa = p;
					}
				}
			}
			else
			{
				printf("Too much sample's size!\n\n");
				sScan t;
				t.n = INT_MAX;
				t.p = 1.0;
				res.push_back( t );
			}

			sort(res.begin(),res.end());
			return res;
		}
};

#endif
