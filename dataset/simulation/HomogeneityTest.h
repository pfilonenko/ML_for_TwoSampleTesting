#ifndef HomogeneityTest_H
#define HomogeneityTest_H

#include"EDF.h"
#include"SearchN.h"
#include"ConvergenceToLimitLaw.h"

// ---- Abstract class of the Two-Sample test ----

class HomogeneityTest : 
	public ConvergenceToLimitLaw, 
	public SearchN
{
	protected:
		double Sn;

	public:
		virtual double F(double x)=0;
		virtual double CalculateStatistic(Sample &A, Sample &B)=0;

		HomogeneityTest()
		{
		};

		void Calc(Sample &A, Sample &B)
		{
			Sn = CalculateStatistic(A,B);
		}

		double S()
		{
			return Sn;
		}

		virtual void TitleTest(char title[])=0;

		virtual string TestType()=0;

		//ïîñ÷èòàòü çíà÷åíèå p-value
		double p_value(Sample &A, Sample &B, int MonteKarloSize = 30000)
		{
			double alpha;
			MP_HT mp;
			mp.H = 1111;
			mp.n1 = A.N();
			mp.n2 = B.N();
			mp.Percent0 = int(A.RealCensoredPercent()/5)*5;
			mp.Percent0 = int(B.RealCensoredPercent()/5)*5;
			mp.num0 = mp.num1 = 1;
			mp.MonteKarloSize = MonteKarloSize;
			mp.NumThreads = omp_get_max_threads();
			mp.Repeat = 1;
			mp.TypeCensored = 3;

			auto S = CalculateStatistic(A,B);
			auto GSH0 = this->SampleStatistics(mp);
			EDF F( GSH0 );
			//Sample(GSH0).Save("HHH.dat");

			if( this->TestType()=="double" )
				alpha = 2*min( F.Probability(S), 1-F.Probability(S) );
			else
				if( this->TestType()=="right" )
					alpha = 1.0 - F.Probability(S);
				else
					alpha = F.Probability(S);

			return alpha;
		}
};

// ---- Classical Two-Sample tests for Uncensored Case ----

class HT_KolmogorovSmirnovTest : public HomogeneityTest
{
	public:
		double CalculateStatistic(Sample &X, Sample &Y)
		{
			X.SortSample();
			Y.SortSample();

			//åñëè âûáîðêè öåíçóðèðîâàííûå, òî ñ÷èòàòü íè÷åãî íå áóäåì
			if( X.IsCensored()==true || Y.IsCensored()==true )
				return 1.0e+100;

			double Dm = -DBL_MAX;
			double Dp = -DBL_MAX;

			EDF G( X.GetSample() );

			double t1,t2;

			for(int i=0; i<Y.N(); i++)
			{
				t1 = G.Probability(Y._X(i)) - double(i)/double(Y.N());
				if( t1 > Dp )
					Dp = t1;

				t2 = double(i+1)/double(Y.N()) - G.Probability(Y._X(i));
				if( t2 > Dm )
					Dm = t2;
			}

			Sn = sqrt( X.N()*Y.N()/( X.N()+Y.N() ) )*(max(Dm,Dp) + ( X.N()+Y.N() )/( 4.6*X.N()*Y.N() ) );

			return Sn;
		}

		double F(double x)
		{
			CRVKolmogorov K;
			return K.CDF(x);
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_KolmogorovSmirnovTest");
		}

		string TestType()
		{
			return "right";
		}
};

class HT_LehmannRosenblatt : public HomogeneityTest
{
	private:
		struct LR_Temp
		{
			double v;
			int s;

			int operator <(LR_Temp A)
			{
				if( this->v < A.v )
					return 1;
				else
					return 0;
			};
		};

		int Find(int S, double v, vector<LR_Temp> &VarRate)
		{
			for(int i=0; i<VarRate.size(); i++)
			{
				if( S==VarRate[i].s && VarRate[i].v==v  )
					return (i+1);
			}
		}

		double Calc(Sample &A, Sample &B, vector<LR_Temp> &VarRate)
		{
			A.SortSample();
			B.SortSample();

			//åñëè âûáîðêè öåíçóðèðîâàííûå, òî ñ÷èòàòü íè÷åãî íå áóäåì
			if( A.IsCensored()==true || B.IsCensored()==true )
				return 1.0e+100;

			double n = A.N();
			double m = B.N();

			double _T1=0,_T2=0,tmp;

			tmp = m*n*(m+n);
			for(int i=0; i<A.N(); i++)
				_T1 += n*pow( Find(1,A._X(i),VarRate) - (i+1), 2 )/tmp;

			for(int i=0; i<B.N(); i++)
				_T2 += m*pow( Find(2,B._X(i),VarRate) - (i+1), 2 )/tmp;

			this->Sn = (_T1 + _T2) - ( 4*m*n-1.0 )/( 6*(m+n) );

			return Sn;
		}

		int SampleSizeA,SampleSizeB;	//ðàçìåð âûáîðêè äëÿ ìîäåëèðîâàíèÿ ðàñïðåäåëåíèÿ ñòàòèñòèêè

	public:
		HT_LehmannRosenblatt()
		{
			SampleSizeA = SampleSizeB = -1;
		}

		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();
			SampleSizeA = A.N();
			SampleSizeB = B.N();

			vector<LR_Temp> VarRate;

			VarRate.resize( A.N()+B.N() );
			int An = A.N();
			int N = VarRate.size();
			for(int i=0; i<An; i++)
			{
				VarRate[i].v = A._X(i);
				VarRate[i].s = 1;
			}
	
			for(int i=An; i<N; i++)
			{
				VarRate[i].v = B._X(i-An);
				VarRate[i].s = 2;
			}
			std::sort(VarRate.begin(),VarRate.end());

			return Calc(A,B,VarRate);
		}
		
		double F(double x)
		{
			HT_LehmannRosenblatt z;
			CRVExponential Exp(0,1);
			vector<double> mas( 16600 );

			SampleSizeA = ( SampleSizeA==-1 || SampleSizeA>200 )? 200 : SampleSizeA;
			SampleSizeB = ( SampleSizeB==-1 || SampleSizeB>200 )? 200 : SampleSizeB;

			omp_set_num_threads( 8 );

			#pragma omp parallel for
			for(int i=0; i<mas.size(); i++)
			{
				int rank = omp_get_thread_num();
				Sample A(Exp,SampleSizeA,GwMT19937[rank]),B(Exp,SampleSizeB,GwMT19937[rank]);
				mas[i] = z.CalculateStatistic(A,B);
			}
			EDF F(mas);
			return F.Probability( x );
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_LehmannRosenblatt");
		}

		string TestType()
		{
			return "right";
		}
};

class HT_AndersonDarlingPetitt : public HomogeneityTest
{
	private:
		struct AD
		{
			double v;
			int s;

			int operator <(AD A)
			{
				if( this->v < A.v )
					return 1;
				else
					return 0;
			};
		};

		double M(int k, int j, vector<AD> &SerS)
		{
			int res = 0;
			for(int i=0; i<SerS.size() && SerS[i].v <= SerS[j].v; i++)
			{
				if( SerS[i].s == k )
					res++;
			}
			return res;
		}

		double Calc(Sample &A, Sample &B, vector<AD> &SerS)
		{
			double _T1,_T2;
			int N = A.N() + B.N();
			_T1 = _T2 = 0.0;

			//int NUM = omp_get_max_threads();
			int NUM = 1;
			omp_set_num_threads(NUM);

			vector<int> dim(NUM);
			vector<double> T1(NUM),T2(NUM);
			for(int i=0; i<NUM; i++)
				dim[i] = (N-1)/NUM;
			int ost = (N-1)%NUM;
			for(int i=0; ost>0; i++,ost--)
				dim[i]++;
			#pragma omp parallel
			{
				double r;
				int rank = omp_get_thread_num();
				int beg = 0;
				for(int i=0; i<rank; i++)
					beg += dim[i];
				int end = beg + dim[rank];

				for(int j=beg; j<end; j++)
				{
					r = (j+1)*(N-(j+1));
					T1[rank] += ( pow( N*M(1,j,SerS) - (j+1)*A.N(), 2 ) )/r;
					T2[rank] += ( pow( N*M(2,j,SerS) - (j+1)*B.N(), 2 ) )/r;
				}
			}

			for(int i=0; i<NUM; i++)
			{
				_T1 += T1[i];
				_T2 += T2[i];
			}
	
			return ( _T1/A.N() + _T2/B.N() )/double(N);
		}

		int SampleSizeA,SampleSizeB;	//ðàçìåð âûáîðêè äëÿ ìîäåëèðîâàíèÿ ðàñïðåäåëåíèÿ ñòàòèñòèêè

	public:
		HT_AndersonDarlingPetitt()
		{
			SampleSizeA = SampleSizeB = -1;
		}

		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();
			SampleSizeA = A.N();
			SampleSizeB = B.N();

			//åñëè âûáîðêè öåíçóðèðîâàííûå, òî ñ÷èòàòü íè÷åãî íå áóäåì
			if( A.IsCensored()==true || B.IsCensored()==true )
				return 1.0e+100;

			vector<AD> SerS;

			SerS.resize( A.N() + B.N() );
			int N = SerS.size();
			int An = A.N();

			for(int i=0; i<An; i++)
			{
				SerS[i].v = A._X(i);
				SerS[i].s = 1;
			}
	
			for(int i=An; i<N; i++)
			{
				SerS[i].v = B._X(i-An);
				SerS[i].s = 2;
			}
			std::sort(SerS.begin(),SerS.end());

			return Calc(A,B,SerS);
		}

		double F(double x)
		{
			HT_AndersonDarlingPetitt z;
			CRVExponential Exp(0,1);
			vector<double> mas( 16600 );

			SampleSizeA = ( SampleSizeA==-1 || SampleSizeA>200 )? 200 : SampleSizeA;
			SampleSizeB = ( SampleSizeB==-1 || SampleSizeB>200 )? 200 : SampleSizeB;

			omp_set_num_threads( 8 );

			#pragma omp parallel for
			for(int i=0; i<mas.size(); i++)
			{
				int rank = omp_get_thread_num();
				Sample A(Exp,SampleSizeA,GwMT19937[rank]),B(Exp,SampleSizeB,GwMT19937[rank]);
				mas[i] = z.CalculateStatistic(A,B);
			}
			EDF F(mas);
			return F.Probability( x );
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_AndersonDarlingPetitt");
		}

		string TestType()
		{
			return "right";
		}
};

// ---- Two-Sample tests for Right-Censored Case ----

class HT_Peto : public HomogeneityTest
{
	private:
		struct Point
		{
			double M;	//çíà÷åíèå
			int C;		//ôëàã öåíçóðèðîâàíî ëè
			int V;		//ïðèíàäëåæíîñòü 1é èëè 2é âûáîðêå (0 èëè 1)
			int rang;	//ðàíã (èñïîëüçóåòñÿ â Ãåõàíå)

			int operator <(Point A)
			{
				if( this->M == A.M )
					if( this->C >= A.C )
						return 0;
					else
						return 1;
				else
					if( this->M < A.M )
						return 1;
					else
						return 0;
			};
		};

		double KaplanMeyerEstimate(vector<Point> &T, int k)
		{
			double res = 1.0;
			for(int i=0; i<k; i++)
			{
				if( T[i].C == 0 )
					res *= double( T.size()-(i+1) )/double( T.size()-(i+1)+1 );
			}
			return res;
		}

	public:
		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();

			vector<Point> T( A.N() + B.N() );
			vector<int> R1( T.size() );

			for(int i=0; i<A.N(); i++)
			{
				T[i].M = A._X(i);
				T[i].C = A._C(i);
				T[i].V = 0;
			}
			for(int i=A.N(), j=0; i<T.size(); i++,j++)
			{
				T[i].M = B._X(j);
				T[i].C = B._C(j);
				T[i].V = 1;
			}
			sort(T.begin(),T.end());

			double S = 1.0;
			double U = 1.0;
			vector<pair<double,double>> SU( T.size() );
			for(int i=0; i<T.size(); i++)
			{
				if( T[i].C == 0 )
				{
					SU[i].first = KaplanMeyerEstimate(T,i+1);

					SU[i].second = S + SU[i].first - 1;
					S = SU[i].first;
				}
				else
				{
					SU[i].first = -1.0;
					SU[i].second = S - 1.0;
				}
			}

			double W = 0;
			double VarW = 0;
			for(int i=0; i<T.size(); i++)
			{
				if( T[i].V==0 )
					W += SU[i].second;
				VarW += pow( SU[i].second, 2 );
			}
			VarW *= double( A.N()*B.N() )/double( ( A.N()+B.N() )*( A.N()+B.N()-1 ) );

			Sn = W/sqrt( VarW );

			return Sn;
		}

		double F(double x)
		{
			CRVNormal N01(0,1);
			return N01.CDF(x);
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_Peto");
		}

		string TestType()
		{
			return "double";
		}
};

class HT_Gehan : public HomogeneityTest
{
	private:
		struct Point
		{
			double M;	//çíà÷åíèå
			int C;		//ôëàã öåíçóðèðîâàíî ëè
			int V;		//ïðèíàäëåæíîñòü 1é èëè 2é âûáîðêå (0 èëè 1)
			int rang;	//ðàíã (èñïîëüçóåòñÿ â Ãåõàíå)

			int operator <(Point A)
			{
				if( this->M == A.M )
					if( this->C >= A.C )
						return 0;
					else
						return 1;
				else
					if( this->M < A.M )
						return 1;
					else
						return 0;
			};
		};

		//Rank from left to right, omitting censored observations
		void Step1(vector<Point> &T)
		{
			int r = 1;
			for(int i=0; i<T.size(); i++)
			{
				if( T[i].C == 0 )
				{
					T[i].rang = r;
					r++;
				}
			}
		}

		//Assign next-higher rank to censored observations
		void Step2(vector<Point> &T)
		{
			int r = 0;
			for(int i=0; i<T.size(); i++)
			{
				if( T[i].C == 0 )
					r = T[i].rang + 1;
				else
					T[i].rang = r;
			}
		}

		//Reduce the rank of tied observations to the lower rank for the value
		void Step3(vector<Point> &T)
		{
			for(int i=1; i<T.size(); i++)
			{
				if( fabs(T[i].M - T[i-1].M)<DBL_EPSILON && T[i].C == T[i-1].C)
					T[i].rang = T[i-1].rang;
			}
		}

		//R1i
		void Step4(vector<Point> &T, vector<int> &R1)
		{
			for(int i=0; i<R1.size(); i++)
				R1[i] = T[i].rang;
		}

		//Rank from right to left
		void Step5(vector<Point> &T)
		{
			for(int i=0; i<T.size(); i++)
				T[i].rang = T.size() - i;
		}

		//Reduce the rank of tied observations to the lowest rank for the value
		void Step6(vector<Point> &T)
		{
			for(int i=0; i<T.size()-1; i++)
			{
				int j = i+1;
				//while(T[i].M == T[j].M && T[i].C == T[j].C)
				while( j<T.size() && T[i].M == T[j].M && T[i].C == T[j].C )	///////////////////////////////////////
					j++;
				
				for(int k=i; k<j; k++)
					T[k].rang = T[j-1].rang;
			}
		}

		//Reduce the rank of censored observations to 1
		void Step7(vector<Point> &T)
		{
			for(int i=0; i<T.size(); i++)
				if( T[i].C == 1 )
					T[i].rang = 1;
		}

		//R2i
		void Step8(vector<Point> &T, vector<int> &R1)
		{
			for(int i=0; i<T.size(); i++)
				T[i].rang = R1[i] - T[i].rang;
		}

	public:
		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();

			vector<Point> T( A.N() + B.N() );
			vector<int> R1( T.size() );

			for(int i=0; i<A.N(); i++)
			{
				T[i].M = A._X(i);
				T[i].C = A._C(i);
				T[i].V = 0;
			}
			for(int i=A.N(), j=0; i<T.size(); i++,j++)
			{
				T[i].M = B._X(j);
				T[i].C = B._C(j);
				T[i].V = 1;
			}
			sort(T.begin(),T.end());

			//Computation of R1i
			Step1(T);
			Step2(T);
			Step3(T);
			Step4(T,R1);

			//Computation of R2i
			Step5(T);
			Step6(T);
			Step7(T);
			Step8(T,R1);

			double W = 0;
			double VarW = 0;
			for(int i=0; i<T.size(); i++)
			{
				if( T[i].V == 0 )
					W += T[i].rang;
				VarW += pow( T[i].rang, 2 );
			}
			VarW *= double( A.N()*B.N() )/double( ( A.N()+B.N() )*( A.N()+B.N()-1 ) );

			Sn = W/sqrt( VarW );

			return Sn;
		}

		double F(double x)
		{
			CRVNormal N01(0,1);
			return N01.CDF(x);
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_Gehan");
		}

		string TestType()
		{
			return "double";
		}
};

class HT_Logrank : public HomogeneityTest
{
	private:
		struct Point
		{
			double T;
			double C;		//ôëàã öåíçóðèðîâàíî ëè

			double M;	//çíà÷åíèå
			double r;		//ðàíã

			int V;		//ïðèíàäëåæíîñòü 1é èëè 2é âûáîðêå (0 èëè 1)

			int operator <(Point A)
			{
				if( this->T == A.T )
					if( this->C > A.C )
						return 0;
					else
						return 1;
				else
					if( this->T < A.T )
						return 1;
					else
						return 0;
			};

			Point()
			{
				T = C = M = r = V = 0;
			}
		};

		int Exsist(double t, vector<Point> &T)
		{
			for(int i=0; i<T.size(); i++)
				if( fabs(T[i].T-t)<=DBL_EPSILON )
					return i;
			return -1;
		}

		double Calc(vector<Point> &XX, double n1, double n2)
		{
			double TEST = 0.0;

			double n = n1 + n2;
			double Lg = 0.0;
			double summ = 0;	//ýòî áóäåì âû÷èòàòü íà êàæäîé èòåðàöèè èç m_i
			double sume = 0.0;	//ê ýòîìó áóäåì ïëþñîâàòü e(t_i)
			double last_e = 0.0;//áóäåì ñîõðàíÿòü çíà÷åíèå, êîòîðîå íàçíà÷àåòñÿ öåíçóðèðîâàííûì
			double vars = 0.0;
			for(int i=0; i<XX.size(); i++)
			{
				if( XX[i].C==0 )
				{
					XX[i].r = n - summ;
					sume += XX[i].M/XX[i].r;
					last_e = sume;

					if( XX[i].V==2 )
						Lg += (1.0-sume)*XX[i].M;
					vars += pow(1.0-sume,2)*XX[i].M;

					TEST += (1.0-sume)*XX[i].M;
				}
				else
				{
					if( XX[i].V==2 )
						Lg += -last_e;
					vars += pow(-last_e,2);

					TEST += -last_e;
				}
				summ += XX[i].M;
			}
			//printf("%.15lf\n",TEST);

			vars *= n1*n2/( n*(n-1) );

			Sn = Lg/sqrt( vars );
			
			return Sn;
		}

	public:
		double CalculateStatistic(Sample &A, Sample &B)
		{
			int k;
			double temp;
			vector<Point> XX;
			for(int i=0; i<A.N(); i++)
			{
				temp = A._X(i);
				if( ( k=Exsist(temp,XX) )!=-1 && XX[k].C==0 )	//????????????????
					XX[k].M++;
				else
				{
					Point P;
					P.T = temp;
					P.C = A._C(i);
					P.M = 1;
					P.V = 1;
					XX.push_back( P );
				}
			}

			for(int i=0; i<B.N(); i++)
			{
				temp = B._X(i);
				if( ( k=Exsist(temp,XX) )!=-1 && XX[k].C==0 )
				{
					XX[k].M++;
					XX[k].V = 2;	//??????????????
				}
				else
				{
					Point P;
					P.T = temp;
					P.C = B._C(i);
					P.M = 1;
					P.V = 2;
					XX.push_back( P );
				}
			}
			sort(XX.begin(),XX.end());

			return Calc(XX, A.N(), B.N());
		}

		double F(double x)
		{
			CRVNormal N01(0,1);
			return N01.CDF(x);
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_Logrank");
		}

		string TestType()
		{
			return "double";
		}
};

class HT_QTest : public HomogeneityTest
{
	private:
		bool KaplanMeyer;	//ïàðàìåòð äëÿ âûáîðà îöåíêè ôóíêöèé íàäåæíîñòè

		int SampleSizeA,SampleSizeB;	//ðàçìåð âûáîðêè äëÿ ìîäåëèðîâàíèÿ ðàñïðåäåëåíèÿ ñòàòèñòèêè

	public:
		HT_QTest()
		{
			this->KaplanMeyer = true;
			SampleSizeA = SampleSizeB = -1;
		}

		HT_QTest(bool set)
		{
			this->KaplanMeyer = set;
			SampleSizeA = SampleSizeB = -1;
		}

		void SetSurvivalEstimator(bool set)
		{
			this->KaplanMeyer = set;
		}

		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();
			SampleSizeA = A.N();
			SampleSizeA = B.N();

			double x1,x2,Q;

			if( this->KaplanMeyer==true )
			{
				KaplanMeyerEstimate S1(A),S2(B);

				x1 = S1.Quantile(0.6);
				x2 = S1.Quantile(0.2);

				Q = fabs( S2.Probability(x1) - S1.Probability(x1) ) - fabs( S2.Probability(x2) - S1.Probability(x2) );
			}
			else
			{
				NelsonAalenSurvivalEstimate S1(A),S2(B);
	
				x1 = S1.Quantile(0.6);
				x2 = S1.Quantile(0.2);

				Q = fabs( S2.Probability(x1) - S1.Probability(x1) ) - fabs( S2.Probability(x2) - S1.Probability(x2) );
			}

			if( Q < 0 )
			{
				//If Q < 0, then use logrank test
				HT_Logrank Lg;
				this->Sn = Lg.CalculateStatistic(A,B);
			}
			else
			{
				//Otherwise, use Wilcoxon test
				HT_Peto P;
				this->Sn = P.CalculateStatistic(A,B);
			}
			return Sn;
		}

		double F(double x)
		{
			HT_QTest z(this->KaplanMeyer);
			CRVExponential Exp(0,1);
			vector<double> mas( 16600 );

			SampleSizeA = ( SampleSizeA==-1 || SampleSizeA>200 )? 200 : SampleSizeA;
			SampleSizeB = ( SampleSizeB==-1 || SampleSizeB>200 )? 200 : SampleSizeB;

			omp_set_num_threads( 8 );

			#pragma omp parallel for
			for(int i=0; i<mas.size(); i++)
			{
				int rank = omp_get_thread_num();
				Sample A(Exp,SampleSizeA,GwMT19937[rank]),B(Exp,SampleSizeB,GwMT19937[rank]);
				mas[i] = z.CalculateStatistic(A,B);
			}
			EDF F(mas);
			return F.Probability( x );
		}

		void TitleTest(char title[])
		{
			if( this->KaplanMeyer==true )
				sprintf(title,"HT_QTest_KM");
			else
				sprintf(title,"HT_QTest_NA");
		}

		string TestType()
		{
			return "double";
		}
};

class HT_MAX : public HomogeneityTest
{
	private:

		int SampleSizeA,SampleSizeB;	//ðàçìåð âûáîðêè äëÿ ìîäåëèðîâàíèÿ ðàñïðåäåëåíèÿ ñòàòèñòèêè

		double F0(double x)
		{
			boost::math::normal_distribution<double> norm_dist(0, 1);
			return cdf(norm_dist, x) - cdf(norm_dist, 0.0);
		}

		double phi(double x)
		{
			return exp(-x*x/2.0)/sqrt(2.0*3.14159265358979323846);
		}

		double func(double x)
		{
			if( x < 0.0 )
				return 0.0;

			//0.867424	N=1660000 n1=n2=1000
			//0.866808	N=1660000 n1=n2=2500
			//0.866578	N=1660000 n1=n2=5000
			//0.8408450570 ïîòåíöèàëüíàÿ àíàëèòèêà

			//double r = 0.866578;	//êîýôôèöèåíò êîððåëÿöèè!!!
			double r = sqrt(3.0)/2.0;	//êîýôôèöèåíò êîððåëÿöèè!!!
			if( fabs(r) == 1.0 )
				return 2.0*phi(x);
			else
				if( r == 0.0 )
					return 8.0*phi(x)*F0(x);
				else
					return 4*phi(x)*( F0( x*sqrt( (1.0-r)/(1.0+r) ) ) + F0( x*sqrt( (1.0+r)/(1.0-r) ) ) );
		}

		double Gauss4(double e, double f)
		{
			std::vector < double > xj ( 4 ), q ( 4 );
			/*
			Points
			*/
			xj [0] = sqrt ( ( 3.0 - 2.0 * sqrt ( 6.0 / 5.0) ) / 7.0 );
			xj [1] = sqrt ( ( 3.0 + 2.0 * sqrt ( 6.0 / 5.0) ) / 7.0 );
			xj [2] = -xj [1];
			xj [3] = -xj [0];
			/*
			Weights
			*/
			q [0] = ( 18 + sqrt ( 30.0 ) ) / 36.0;
			q [1] = ( 18 - sqrt ( 30.0 ) ) / 36.0;
			q [2] = q [1];
			q [3] = q [0];

			double summ = 0;
			double s = 0;
			double theta;

			for ( int k = 0; k < 4; ++k )
			{
				theta = ( e + f + xj [k] * ( f - e ) ) / 2.0;
				s += q[k] * func(theta);
			}
	
			summ += s *(f-e) / (2.0);

			return summ;
		}

	public:
		HT_MAX()
		{
			SampleSizeA = SampleSizeB = -1;
		}

		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();
			SampleSizeA = A.N();
			SampleSizeB = B.N();

			HT_Logrank T1;
			HT_Gehan T2;

			double S1 = fabs(T1.CalculateStatistic(A,B));
			double S2 = fabs(T2.CalculateStatistic(A,B));

			if( S1 > S2 )
				Sn = S1;
			else
				Sn = S2;

			return Sn;
		}

		double F(double x)
		{
			double h = 0.05;
			double res = 0.0;
			double a,b;
			bool P = true;
			a = 0;
			b = a + h;
			while(P)
			{
				if( b>x )
				{
					b = x;
					P = false;
				}

				res += Gauss4(a,b);

				a = b;
				b += h;
			}

			return (res>1.0)? 1.0 : res;
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_MAX");
		}

		string TestType()
		{
			return "right";
		}
};

class HT_BagdonaviciusNikulinGeneralizedCox : public HomogeneityTest
{
//For the GPH and SCE models U=(U1,U2)
//In the case of the statistic U obtained from the score function under the GPH model the second component U2=0 and so in this case we take U=U1
//The statistic U is one-, two- or three dimensional when it is obtained using the GPH, SCE or MCE model, respectively.
	private:
		struct MDT_struct
		{
			double X;	//çíà÷åíèå
			int V;		//ïðèíàäëåæíîñòü ê âûáîðêå

			int operator <(MDT_struct A)
			{
				if(this->X < A.X)
					return 1;
				else
					return 0;
			};
		};

		//Y_1(t)
		double Y(int num, double t, Sample &A, Sample &B)
		{
			Sample *C = NULL;
			if(num==1)
				C = &A;
			else
				C = &B;

			double res = 0.0;
			int N = C->N();
			for(int i=0; i<N; i++)
			{
				if( C->_X(i) >= t )
					res++;
			}
			return res;
		}

		//N_1
		double N(int num, double t, Sample &A, Sample &B)
		{
			Sample *C = NULL;
			if(num==1)
				C = &A;
			else
				C = &B;

			double res = 0.0;
			int N = C->N();
			for(int i=0; i<N; i++)
			{
				if( C->_X(i)<=t && C->_C(i)==0 )
					res++;
			}
			return res;
		}

		double Calc(Sample &A, Sample &B, vector<MDT_struct> &XX, double DBL_EPS_MD)
		{
			double u1,u2,E11,E12,E22;
			u1 = u2 = E11 = E12 = E22 = 0.0;

			double y1,y2,lam1_last,lam1_new,lam2_last,lam2_new,n1_new,n1_last,n2_new,n2_last,lambda_new,lambda_last;
			y1 = A.N();	y2 = B.N();
			lam1_last = lam1_new = lam2_last = lam2_new = 0.0;
			n1_new = n1_last = n2_new = n2_last = lambda_new = lambda_last = 0.0;

			for(int i=0; i<XX.size(); i++)
			{
				//y1 = Y(1,XX[i].X,A,B);
				//y2 = Y(2,XX[i].X,A,B);

				n1_new = N(1,XX[i].X+DBL_EPS_MD,A,B);
				n2_new = N(2,XX[i].X+DBL_EPS_MD,A,B);
		
				lambda_new = lambda_last + ( (n1_new+n2_new)-(n1_last+n2_last) )/(y1+y2);

				if( fabs(n1_new-n1_last)<=DBL_EPSILON && fabs(y1)<=DBL_EPSILON )
					lam1_new = lam1_last + 1.0;
				else
					if(fabs(y1)>DBL_EPSILON)
						lam1_new = lam1_last + ( (n1_new-n1_last)/y1 );
					else
						lam1_new = lam1_last + 0.0;

				if( fabs(n2_new-n2_last)<=DBL_EPSILON && fabs(y2)<=DBL_EPSILON )
					lam2_new = lam2_last + 1.0;
				else
					if(fabs(y2)>DBL_EPSILON)
						lam2_new = lam2_last + ( (n2_new-n2_last)/y2 );
					else
						lam2_new = lam2_last + 0.0;

				double a1 = y1*y2/(y1+y2);
				double a2 = (lam2_new-lam1_new)-(lam2_last-lam1_last);
				double a3 = log( 1 + lambda_last );
				double a4 = (n1_new+n2_new)-(n1_last+n2_last);

				u1 += a1 * a2;
				u2 -= a1 * a3 * a2;

				E11 += a1/(y1+y2) * ( a4 );
				E12 -= a1/(y1+y2) * a3 * a4;
				E22 += a1/(y1+y2) * pow( a3, 2 ) * a4;

				//êîððåêòíî
				lam1_last = lam1_new;
				lam2_last = lam2_new;

				n1_last = n1_new;
				n2_last = n2_new;

				if( XX[i].V==1 )
					y1--;
				else
					y2--;

				lambda_last = lambda_new;
			}

			double det = E11*E22 - E12*E12;
			double A11,A12,A22;
			A11 = E22/det;
			A12 = -E12/det;
			A22 = E11/det;

			double t1,t2;
			t1 = u1*A11 + u2*A12;
			t2 = u1*A12 + u2*A22;

			Sn = t1*u1 + t2*u2;

			return Sn;
		}

	public:
		double CalculateStatistic(Sample &A, Sample &B)
		{
			vector<MDT_struct> XX;
			double DBL_EPS_MD = 1e-13;

			for(int i=0; i<A.N(); i++)
			{
				MDT_struct Temp;
				Temp.X = A._X(i);
				Temp.V = 1;
				XX.push_back(Temp);
			}
			for(int i=0; i<B.N(); i++)
			{
				MDT_struct Temp;
				Temp.X = B._X(i);
				Temp.V = 2;
				XX.push_back(Temp);
			}
			std::sort(XX.begin(),XX.end());

			return Calc(A,B,XX,DBL_EPS_MD);
		}

		double F(double x)
		{
			CRVChiSquare CS(0,2);
			return CS.CDF(x);
		}

		void TitleTest(char title[])
		{
			//sprintf(title,"HT_BN1");
			sprintf(title,"HT_BagdonaviciusNikulinGeneralizedCox");
		}

		string TestType()
		{
			return "right";
		}
};

class HT_BagdonaviciusNikulinMultiple : public HomogeneityTest
{
//ÏÅÐÅÏÈÑÀÍ ÏÎ ÑÒÀÒÜÅ 2006 ÃÎÄÀ!!! Èñïðàâëåíû íåòî÷íîñòè ðåàëèçàöèè â êðèòåðèè BN2
//For the MCE model U=(U1,U2,U3)
//The statistic U is one-, two- or three dimensional when it is obtained using the GPH, SCE or MCE model, respectively.
	private:
		struct MDT_struct
		{
			double X;	//çíà÷åíèå
			int V;		//ïðèíàäëåæíîñòü ê âûáîðêå

			int operator <(MDT_struct A)
			{
				if(this->X < A.X)
					return 1;
				else
					return 0;
			};
		};

		//Y_1(t)
		double Y(int num, double t, Sample &A, Sample &B)
		{
			Sample *C = NULL;
			if(num==1)
				C = &A;
			else
				C = &B;

			double res = 0.0;
			int N = C->N();
			for(int i=0; i<N; i++)
			{
				if( C->_X(i) >= t )
					res++;
			}
			return res;
		}

		//N_1
		double N(int num, double t, Sample &A, Sample &B)
		{
			Sample *C = NULL;
			if(num==1)
				C = &A;
			else
				C = &B;

			double res = 0.0;
			int N = C->N();
			for(int i=0; i<N; i++)
			{
				if( C->_X(i)<=t && C->_C(i)==0 )
					res++;
			}
			return res;
		}

		double Calc(Sample &A, Sample &B, vector<MDT_struct> &XX, double DBL_EPS_MD)
		{
			double u1,u2,u3,E11,E12,E22,E23,E33;
			u1 = u2 = u3 = E11 = E12 = E22 = E23 = E33 = 0.0;

			double y1,y2,lam1_last,lam1_new,lam2_last,lam2_new,n1_new,n1_last,n2_new,n2_last,lambda_new,lambda_last;
			y1 = A.N();	y2 = B.N();
			lam1_last = lam1_new = lam2_last = lam2_new = 0.0;
			n1_new = n1_last = n2_new = n2_last = lambda_new = lambda_last = 0.0;

			for(int i=0; i<XX.size(); i++)
			{
				n1_new = N(1,XX[i].X+DBL_EPS_MD,A,B);
				n2_new = N(2,XX[i].X+DBL_EPS_MD,A,B);
		
				lambda_new = lambda_last + ( (n1_new+n2_new)-(n1_last+n2_last) )/(y1+y2);

				if( fabs(n1_new-n1_last)<=DBL_EPSILON && fabs(y1)<=DBL_EPSILON )
					lam1_new = lam1_last + 1.0;
				else
					if(fabs(y1)>DBL_EPSILON)
						lam1_new = lam1_last + ( (n1_new-n1_last)/y1 );
					else
						lam1_new = lam1_last + 0.0;

				if( fabs(n2_new-n2_last)<=DBL_EPSILON && fabs(y2)<=DBL_EPSILON )
					lam2_new = lam2_last + 1.0;
				else
					if(fabs(y2)>DBL_EPSILON)
						lam2_new = lam2_last + ( (n2_new-n2_last)/y2 );
					else
						lam2_new = lam2_last + 0.0;

				double a1 = y1*y2/(y1+y2);
				double a2 = (lam2_new-lam1_new)-(lam2_last-lam1_last);
				double a3 = lambda_last;
				double a4 = (n1_new+n2_new)-(n1_last+n2_last);

				u1 += a1 * a2;
				u2 += a1 * a3 * a2;
				u3 += a1 * pow( a3, 2 ) * a2;

				E11 += a1/(y1+y2) * ( a4 );
				E12 += a1/(y1+y2) * a3 * a4;
				E22 += a1/(y1+y2) * pow( a3, 2 ) * a4;
				E23 += a1/(y1+y2) * pow( a3, 3 ) * a4;
				E33 += a1/(y1+y2) * pow( a3, 4 ) * a4;

				//êîððåêòíî
				lam1_last = lam1_new;
				lam2_last = lam2_new;

				n1_last = n1_new;
				n2_last = n2_new;

				lambda_last = lambda_new;

				if( XX[i].V==1 )
					y1--;
				else
					y2--;
			}

			double E13,E31,E32,E21;
			E21 = E12;
			E13 = E31 = E22;
			E32 = E23;

			double det,S[3][3];
			det = E31*E12*E23-E31*E13*E22-E21*E12*E33+E21*E13*E32+E11*E22*E33-E11*E23*E32;
			S[0][0] = ( E22*E33-E23*E32  )/det;	S[0][1] = ( -E12*E33+E13*E32 )/det;	S[0][2] = ( E12*E23-E13*E22  )/det;
			S[1][0] = ( E31*E23-E21*E33  )/det;	S[1][1] = ( -E31*E13+E11*E33 )/det;	S[1][2] = ( E21*E13-E11*E23  )/det;
			S[2][0] = ( -E31*E22+E21*E32 )/det;	S[2][1] = ( E31*E12-E11*E32  )/det;	S[2][2] = ( -E21*E12+E11*E22 )/det;

			Sn = S[0][0]*u1*u1 + S[1][1]*u2*u2 + S[2][2]*u3*u3 + 2*S[0][1]*u1*u2 + 2*S[0][2]*u1*u3 + 2*S[1][2]*u2*u3;

			return Sn;
		}

	public:
		double CalculateStatistic(Sample &A, Sample &B)
		{
			vector<MDT_struct> XX;
			double DBL_EPS_MD = 1e-13;

			for(int i=0; i<A.N(); i++)
			{
				MDT_struct Temp;
				Temp.X = A._X(i);
				Temp.V = 1;
				XX.push_back(Temp);
			}
			for(int i=0; i<B.N(); i++)
			{
				MDT_struct Temp;
				Temp.X = B._X(i);
				Temp.V = 2;
				XX.push_back(Temp);
			}
			std::sort(XX.begin(),XX.end());

			return Calc(A,B,XX,DBL_EPS_MD);
		}

		double F(double x)
		{
			CRVChiSquare CS(0,3);
			return CS.CDF(x);
		}

		void TitleTest(char title[])
		{
			//sprintf(title,"HT_BN2");
			sprintf(title,"HT_BagdonaviciusNikulinMultiple");
		}

		string TestType()
		{
			return "right";
		}
};

class HT_BagdonaviciusNikulinSingle : public HomogeneityTest
{
//nonparametric_tests_for_censored_data_vilijandas_bagdonavici, p.93
	private:
		struct MDT_struct
		{
			double X;	//çíà÷åíèå
			int C;
			int V;		//ïðèíàäëåæíîñòü ê âûáîðêå

			int operator <(MDT_struct A)
			{
				if(this->X < A.X)
					return 1;
				else
					return 0;
			};
		};

		//Y_1(t)
		double Y(int num, double t, Sample &A, Sample &B)
		{
			Sample *C = NULL;
			if(num==1)
				C = &A;
			else
				C = &B;

			double res = 0.0;
			int N = C->N();
			for(int i=0; i<N; i++)
			{
				if( C->_X(i) >= t )
					res++;
			}
			return res;
		}

		//N_1
		double N(int num, double t, Sample &A, Sample &B)
		{
			Sample *C = NULL;
			if(num==1)
				C = &A;
			else
				C = &B;

			double res = 0.0;
			int N = C->N();
			for(int i=0; i<N; i++)
			{
				if( C->_X(i)<=t && C->_C(i)==0 )
					res++;
			}
			return res;
		}

		double K(int num, double expL, int n)
		{
			if( num==1 )						//çàêîììåíòèðîâàííîå äàåò BN1
				return expL/sqrt( double(n) );
				//return 1.0/sqrt( double(n) );
			else
				return (expL-1.0)/sqrt( double(n) );
				//return -log(1.0 - log(expL) )/sqrt( double(n) );
		}

		double Calc(Sample &A, Sample &B, vector<MDT_struct> &XX, double DBL_EPS_MD)
		{
			double u1,u2,E11,E12,E22;
			u1 = u2 = E11 = E12 = E22 = 0.0;

			double y1,y2,lam1_last,lam1_new,lam2_last,lam2_new,n1_new,n1_last,n2_new,n2_last,lambda_new,lambda_last;
			y1 = A.N();	y2 = B.N();
			lam1_last = lam1_new = lam2_last = lam2_new = 0.0;
			n1_new = n1_last = n2_new = n2_last = lambda_new = lambda_last = 0.0;

			for(int i=0; i<XX.size(); i++)
			{
				n1_new = N(1,XX[i].X+DBL_EPS_MD,A,B);
				n2_new = N(2,XX[i].X+DBL_EPS_MD,A,B);
		
				lambda_new = lambda_last + ( (n1_new+n2_new)-(n1_last+n2_last) )/(y1+y2);

				if( fabs(n1_new-n1_last)<=DBL_EPSILON && fabs(y1)<=DBL_EPSILON )
					lam1_new = lam1_last + 1.0;
				else
					if(fabs(y1)>DBL_EPSILON)
						lam1_new = lam1_last + ( (n1_new-n1_last)/y1 );
					else
						lam1_new = lam1_last + 0.0;

				if( fabs(n2_new-n2_last)<=DBL_EPSILON && fabs(y2)<=DBL_EPSILON )
					lam2_new = lam2_last + 1.0;
				else
					if(fabs(y2)>DBL_EPSILON)
						lam2_new = lam2_last + ( (n2_new-n2_last)/y2 );
					else
						lam2_new = lam2_last + 0.0;

				double a1 = y1*y2/(y1+y2);
				double a2 = (lam2_new-lam1_new)-(lam2_last-lam1_last);
				
				double K1 = K(1, exp(-lambda_last), XX.size() );
				double K2 = K(2, exp(-lambda_last), XX.size() );

				u1 += a1 * a2 * K1;
				u2 += a1 * a2 * K2;

				E11 += ( 1.0-XX[i].C )*K1*K1*a1/(y1+y2);
				E12 += ( 1.0-XX[i].C )*K1*K2*a1/(y1+y2);
				E22 += ( 1.0-XX[i].C )*K2*K2*a1/(y1+y2);

				//êîððåêòíî
				lam1_last = lam1_new;
				lam2_last = lam2_new;

				n1_last = n1_new;
				n2_last = n2_new;

				if( XX[i].V==1 )
					y1--;
				else
					y2--;

				lambda_last = lambda_new;
			}

			double det = E11*E22 - E12*E12;
			double A11,A12,A22;
			A11 = E22/det;
			A12 = -E12/det;
			A22 = E11/det;

			double t1,t2;
			t1 = u1*A11 + u2*A12;
			t2 = u1*A12 + u2*A22;

			Sn = t1*u1 + t2*u2;

			return Sn;
		}

	public:
		double CalculateStatistic(Sample &A, Sample &B)
		{
			vector<MDT_struct> XX;
			double DBL_EPS_MD = 1e-13;

			for(int i=0; i<A.N(); i++)
			{
				MDT_struct Temp;
				Temp.X = A._X(i);
				Temp.C = A._C(i);
				Temp.V = 1;
				XX.push_back(Temp);
			}
			for(int i=0; i<B.N(); i++)
			{
				MDT_struct Temp;
				Temp.X = B._X(i);
				Temp.C = B._C(i);
				Temp.V = 2;
				XX.push_back(Temp);
			}
			std::sort(XX.begin(),XX.end());

			return Calc(A,B,XX,DBL_EPS_MD);
		}

		double F(double x)
		{
			CRVChiSquare CS(0,2);
			return CS.CDF(x);
		}

		void TitleTest(char title[])
		{
			//sprintf(title,"HT_BN3");
			sprintf(title,"HT_BagdonaviciusNikulinSingle");
		}

		string TestType()
		{
			return "right";
		}
};

class HT_WeightedLogrank : public HomogeneityTest
{
//nonparametric_tests_for_censored_data_vilijandas_bagdonavici, p.80
	private:
		int Sel;	//âûáîð ôóíêöèè Ê

		double K(double Y, int n, double Sm)
		{
			switch( Sel )
			{
				case 1:
					return 1.0/sqrt( n );				//logrank statistic (Cox, MantelHaenszel)
				case 2:
					return sqrt(Y)/double(n);			//TaroneWare statistic
				case 3:
					return Y/pow( double(n), 3.0/2.0 );	//Breslow statistic (generalization of the KruskalWallis statistic):
				case 4:
					return Sm/sqrt( double(n) );		//PetoPrentice statistic
				case 5:
					return Sm*Y/( sqrt(double(n))*(Y+1) );	//Prentice statistic
			}
		}

		double Y(int num, double t, Sample &A, Sample &B)
		{
			Sample *C = NULL;
			if(num==1)
				C = &A;
			else
				C = &B;

			double res = 0.0;
			int N = C->N();
			for(int i=0; i<N; i++)
			{
				if( C->_X(i) >= t )
					res++;
			}
			return res;
		}

	public:
		HT_WeightedLogrank()
		{
			Sel = 1;
		}

		HT_WeightedLogrank(char modification[])
		{
			if( strcmp(modification,"Prentice")==0 )
				Sel = 5;
			else
				if( strcmp(modification,"PetoPrentice")==0 )
					Sel = 4;
				else
					if( strcmp(modification,"Breslow")==0 )
						Sel = 3;
					else
						if( strcmp(modification,"TaroneWare")==0 )
							Sel = 2;
						else
							Sel = 1;	//logrank
		}

		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();

			KaplanMeyerEstimate KMA(A),KMB(B);

			double V,Sigma,y1,y2,Kx,X;
			V = Sigma = 0.0;

			for(int i=0; i<A.N(); i++)
			{
				X = A._X(i);

				y1 = Y( 1, X, A,B );
				y2 = Y( 2, X, A,B );

				Kx = K( y1+y2, A.N()+B.N(), 1.0 - KMA.Probability(X-DBL_EPSILON) );

				V += (1.0-A._C(i))*Kx*y2/(y1+y2);
				Sigma += (1.0-A._C(i))*pow( Kx, 2.0 )*y1*y2/pow(y1+y2, 2.0);
			}

			for(int i=0; i<B.N(); i++)
			{
				X = B._X(i);

				y1 = Y( 1, X, A,B );
				y2 = Y( 2, X, A,B );

				Kx = K( y1+y2, A.N()+B.N(), 1.0 - KMA.Probability(X-DBL_EPSILON) );

				V -= (1.0-B._C(i))*Kx*y1/(y1+y2);
				Sigma += (1.0-B._C(i))*pow( Kx, 2.0 )*y1*y2/pow(y1+y2, 2.0);
			}

			if( fabs(V)<=DBL_EPSILON && fabs(Sigma)<=DBL_EPSILON )
				return 1.0;
			else
				return V*V/Sigma;
		}

		double F(double x)
		{
			CRVGamma G(0.0, 2.0, 0.5);
			return G.CDF(x);
		}

		void TitleTest(char title[])
		{
			switch( Sel )
			{
				case 1:
					sprintf(title,"HT_WeightedLogrank_K[1_logrank]");
					break;
				case 2:
					sprintf(title,"HT_WeightedLogrank_K[2_TaroneWare]");
					break;
				case 3:
					sprintf(title,"HT_WeightedLogrank_K[3_Breslow]");
					break;
				case 4:
					sprintf(title,"HT_WeightedLogrank_K[4_PetoPrentice]");
					break;
				case 5:
					sprintf(title,"HT_WeightedLogrank_K[5_Prentice]");
					break;
			}
		}

		string TestType()
		{
			return "right";
		}
};

class HT_WeightedKaplanMeyer : public HomogeneityTest
{
//A jackknife-based versatile test for two-sample problems with rightcensored data [Yu-Mei Chang, Chun-Shu Chen, Pao-Sheng Shen]
	private:
		struct sKM
		{
			double X;
			int C;
			int v;

			bool operator<(sKM &A)
			{
				if( X==A.X )
				{
					if( C<A.C )
						return true;
					else
						return false;
				}
				else
				{
					if( X<A.X )
						return true;
					else
						return false;
				}
			}
		};

		double DBL_EPS;

		double Calc(Sample &S1, Sample &C1, Sample &S2, Sample &C2, Sample &S, vector<sKM> &XX)
		{
			KaplanMeyerEstimate KS1(S1),KS2(S2),KC1(C1),KC2(C2),KS(S);

			int n1 = S1.N(),n2 = S2.N();
			double V = 0,Sig = 0,t,c1,c2,s,smin,w,temp,sum = 0.0;
			for(int i=XX.size()-1; i>-1; i--)
			{
				t = XX[i].X;
				c1 = KC1.Probability(t-DBL_EPS);
				c2 = KC2.Probability(t-DBL_EPS);
				s = KS.Probability(t);
				smin = KS.Probability(t-DBL_EPS);

				w = ( fabs(c1)<=DBL_EPSILON && fabs(c2)<=DBL_EPSILON )? 
					1.0 : ( (n1+n2)*c1*c2 )/( n1*c1+n2*c2 );

				V += w*( KS2.Probability(t)-KS1.Probability(t) );
				
				temp = ( fabs(w)>DBL_EPSILON && fabs(s)>DBL_EPSILON && fabs(smin)>DBL_EPSILON )? (s-smin)/(s*smin) : 0.0;
				sum += w*s;
				Sig -= sum*sum*temp;
			}

			V *= sqrt( (1.0*S1.N()*S2.N())/(S1.N()+S2.N()) );
			Sn = V/sqrt( Sig );

			return Sn;
		}

	public:
		double CalculateStatistic(Sample &A, Sample &B)
		{
			A.SortSample();
			B.SortSample();

			DBL_EPS = 1.0e-10;

			sKM Temp;
			vector<sKM> XX;

			vector<double> m1,m2,m;
			vector<int> c1,c2,c;
			for(int i=0; i<A.N(); i++)
			{
				m1.push_back( A._X(i) );
				c1.push_back( 1 - A._C(i) );

				m.push_back( A._X(i) );
				c.push_back( A._C(i) );

				Temp.X = A._X(i);
				Temp.C = A._C(i);
				Temp.v = 1;
				XX.push_back( Temp );
			}
			for(int i=0; i<B.N(); i++)
			{
				m2.push_back( B._X(i) );
				c2.push_back( 1 - B._C(i) );

				m.push_back( B._X(i) );
				c.push_back( B._C(i) );

				Temp.X = B._X(i);
				Temp.C = B._C(i);
				Temp.v = 2;
				XX.push_back( Temp );
			}
			sort( XX.begin(),XX.end() );
			
			//Ñ1 è Ñ2 îíè óæå áóäóò îòñîðòèðîâàíû
			Sample C1(m1,c1),C2(m2,c2),S(m,c);
			S.SortSample();

			return Calc( A,C1,B,C2, S, XX );
		}

		double F(double x)
		{
			CRVNormal N(0,1);
			return N.CDF(x);
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_WeightedKaplanMeyer");
		}

		string TestType()
		{
			return "double";
		}
};

class HT_SynthesisTest : public HomogeneityTest
{
	private:
		double a1, a2, a3;
		EDF *GSH0;

	public:
		HT_SynthesisTest()
		{
			a1 = 1.0;
			a2 = 1.0;
			a3 = 1.0;

			
			//Ñìîäåëèðîâàëè ïðåäåëüíîå ðàñïðåäåëåíèå
			//int N = 30000;
			/*int N = 5;
			vector<double> Sn( N );
			
			#pragma omp parallel for
			for(int i=0; i<N; i++)
			{
				int rank = omp_get_thread_num();
				Sample A(CRVExponential(0,1),100,GwMT19937[rank]);
				Sample B(CRVExponential(0,1),100,GwMT19937[rank]);
				Sn[i] = this->CalculateStatistic( A, B );
			}
			this->GSH0 = new EDF(Sn);*/
		}
		
		HT_SynthesisTest(vector<double> &p)
		{
			a1 = p[0];
			a2 = p[1];
			a3 = p[2];
		}

		double CalculateStatistic(Sample &A, Sample &B)
		{
			HT_WeightedKaplanMeyer T1;
			HT_BagdonaviciusNikulinMultiple T2;
			//HT_BagdonaviciusNikulin_MonotonicHazardRatesRatio T3;
			HT_BagdonaviciusNikulinSingle T3;

			double S1, S2, S3;
			S1 = T1.CalculateStatistic(A,B);
			S2 = T2.CalculateStatistic(A,B);
			S3 = T3.CalculateStatistic(A,B);

			double pv1, pv2, pv3;
			pv1 = 2*min( T1.F(S1), 1-T1.F(S1) );
			pv2 = 1.0 - T2.F(S2);
			pv3 = 1.0 - T3.F(S3);

			double Sn1, Sn2, Sn3;
			Sn1 = a1 * pv1;
			Sn2 = a2 * pv2;
			Sn3 = a3 * pv3;

			return min( Sn1, min( Sn2, Sn3 ) );
		}

		double F(double x)
		{
			return GSH0->Probability(x);
		}

		void TitleTest(char title[])
		{
			sprintf(title,"HT_SynthesisTest");
		}

		string TestType()
		{
			return "left";
		}
};

#endif
