#ifndef Sample_H
#define Sample_H

#include<vector>
#include<iostream>
#include"Distribution.h"
#include"mt19937boost.h"
#include"RNGPool.h"
using namespace std;

class Sample
{
	private:
		vector<double> mas;
		vector<double> C;	// censoring flags

		bool isCensored;	// flag whether the sample is censored?

		char Information[512];	//distribution names (is generated when outputting to file)

		double PracticeCensoredPercent;	// actual degree of censorship

	public:
		Sample(char *filename)
		{
			PracticeCensoredPercent = 0.0;
			FILE *in = fopen(filename,"r");
			
			bool P=true;
			vector<char> ch;
			do{
				char t;
				fscanf(in,"%c",&t);
				if( t=='\n' )
					P = false;
				else
					ch.push_back( t );
			}while(P);

			char *str = new char[ch.size()+1];
			for(int i=0; i<ch.size(); i++)
			{
				if( ch[i]!=' ' )
					str[i] = ch[i];
				else
					str[i] = '_';
			}
			str[ch.size()] = '\0';

			strcpy(this->Information,str);

			delete [] str;

			int Type,Size;
			fscanf(in, "%d%d", &Type,&Size);
			mas.resize(Size);	C.resize(Size);
			if(Type==0)
			{
				//it is an ISW's file
				this->isCensored = false;
				for(int i=0; i<Size; i++)
				{
					fscanf(in,"%lf",&mas[i]);
					C[i] = 0;
				}
			}
			else
			{
				//it is an censored sample
				for(int i=0; i<Size; i++)
				{
					fscanf(in,"%lf%lf",&mas[i],&C[i]);

					if( C[i] )
						PracticeCensoredPercent++;
				}
				PracticeCensoredPercent = 100.0*PracticeCensoredPercent/double(Size);

				if( PracticeCensoredPercent == 0 )
					this->isCensored = false;
				else
					this->isCensored = true;
			}

			fclose(in);
		}

		Sample(Distribution &D, int n, mt19937boost &Gw)
		{
			isCensored = false;	// no, the sample is uncensored
			PracticeCensoredPercent = 0.0;

			//making Information
			D.GetDistributionInformation(Information);

			mas.resize( n );
			C.resize( n, 0.0 );
			for(unsigned int i=0; i<mas.size(); i++)
				mas[i] = D.Quantile( Gw.MT19937Uniform01() );
		}

		Sample(vector<double> &T, vector<int> &c)
		{
			PracticeCensoredPercent = 0;

			if( T.size()==c.size() )
			{
				mas.resize( T.size() );
				this->C.resize( c.size() );
				for(unsigned int i=0; i<mas.size(); i++)
				{
					mas[i] = T[i];
					this->C[i] = c[i];

					if( c[i] )
						PracticeCensoredPercent++;
				}
				PracticeCensoredPercent = 100.0*PracticeCensoredPercent/mas.size();
				
				if( fabs(PracticeCensoredPercent)<=DBL_EPSILON )
					this->isCensored = false;
				else
					this->isCensored = true;
			}
			else
			{
				printf("Different sizes!\n");
				exit(1);
			}
		}

		Sample(vector<double> &T)
		{
			this->isCensored = false;

			PracticeCensoredPercent = 0;

			sprintf(Information,"Non-censored sample. Size: %d",T.size());

			mas.resize( T.size() );
			this->C.resize( T.size(),0.0 );
			for(unsigned int i=0; i<mas.size(); i++)
				mas[i] = T[i];
		}

		void Save(char *filename)
		{
			FILE * ou = fopen(filename,"w");

			if( this->isCensored==false )
			{
				fprintf(ou,"%s\n0 %d\n\n",this->Information,mas.size());
				for(int i=0; i<mas.size(); i++)
					fprintf(ou,"%.15lf\n",mas[i]);
			}
			else
			{
				fprintf(ou,"%s\n1 %d\n\n",this->Information,mas.size());
				for(int i=0; i<mas.size(); i++)
					fprintf(ou,"%.15lf %d\n",mas[i], int(C[i]));
			}

			fclose(ou);
		}

		bool IsCensored()
		{
			return this->isCensored;
		}

		double _X(int i)
		{
			if( i<mas.size() )
				return mas[i];
			else
				return DBL_MAX;
		}

		double _C(int i)
		{
			if( i<mas.size() )
				return this->C[i];
			else
				return DBL_MAX;
		}

		double Mean()
		{
			if( this->isCensored==false )
			{
				double res = 0.0;
				for(unsigned int i=0; i<mas.size(); i++)
					res += mas[i];
				return ( double(res)/double(mas.size()) );
			}
		}
		
		double Variance()
		{
			if( this->isCensored==false )
			{
				double M = this->Mean();
				double res = 0.0;
				for(unsigned int i=0; i<mas.size(); i++)
					res += pow( mas[i] - M, 2 );
				return double( res/mas.size() );
			}
		}
		
		double UnshiftedVariance()
		{
			if( this->isCensored==false )
			{
				double M = this->Mean();
				double res = 0.0;
				for(unsigned int i=0; i<mas.size(); i++)
					res += pow( mas[i] - M, 2 );
				return double( res/(mas.size()-1) );
			}
		}

		// Pearson correlation coefficient
		double PirsonCorrelation(Sample &S)
		{
			if( this->IsCensored()==false && S.IsCensored()==false )	// if the samples are uncensored,
			{
				// then we calculate using the usual formulas

				if( this->N()==S.N())	// if the sample sizes are equal, then we consider
				{
					double mC = this->Mean();
					double mS = S.Mean();

					double sum,sum1,sum2;
					sum = sum1 = sum2 = 0;
					for(int i=0; i<S.N(); i++)
					{
						sum += (this->_X(i)-mC)*(S._X(i)-mS);
						sum1 += pow(this->_X(i)-mC, 2 );
						sum2 += pow(S._X(i)-mS, 2 );
					}

					sum = sum/sqrt( sum1*sum2 );

					return sum;
				}
				else  // otherwise it cannot be calculated
					return 0.0;
			}
			else
			{
				// there should be calculations here for censored samples
				return 0.0;
			}
		}

		double Quantile(double p)
		{
			if( this->isCensored==false )
			{
				if(p>1e-16 && p<1.0)
				{
					vector<double> Temp;
					Temp = this->mas;
					sort(Temp.begin(), Temp.end() );

					int k = mas.size()*p + 1;
					return Temp[k];
				}
				else
					return -DBL_MAX;
			}
		}
		
		double Median()
		{
			if( this->isCensored==false )
			{
				vector<double> Temp;
				Temp = this->mas;
				sort(Temp.begin(), Temp.end() );

				int k;
				if( Temp.size()%2 != 0 )
				{
					// if ODD
					k = Temp.size()/2;
					return Temp[k];
				}
				else
				{
					// if even
					k = Temp.size()/2;
					return ( Temp[k-1] + Temp[k] )*0.5;
				}
			}
		}

		// Sample moment of order k
		double SampleMoment(int k)
		{
			if( this->isCensored==false )
			{
				double res = 0.0;
				for(unsigned int i=0; i<mas.size(); i++)
					res += pow( mas[i], k );
				return double( res/mas.size() );
			}
		}

		// k-th central moment
		double SampleCentralMoment(int k)
		{
			if( this->isCensored==false )
			{
				double M = this->Mean();
				double res = 0.0;
				for(unsigned int i=0; i<mas.size(); i++)
					res += pow( mas[i] - M, k );
				return double( res/mas.size() );
			}
		}

		// sort the sample - get a variation series
		void SortSample()
		{
			if( this->isCensored==false )
			{
				sort( this->mas.begin(), this->mas.end() );
			}
			else
			{
				struct Sorting
				{
					double t;
					int c;

					bool operator <(Sorting &A)
					{
						if( t<A.t )
							return true;
						else
							if( fabs(t-A.t)<=DBL_EPSILON )
							{
								if( c < A.c )
									return true;
								else
									return false;
							}
							else
								return false;
					};
				};
				vector<Sorting> MS( mas.size() );

				for(unsigned int i=0; i<MS.size(); i++)
				{
					MS[i].t = mas[i];
					MS[i].c = C[i];
				}

				sort( MS.begin(), MS.end() );

				for(unsigned int i=0; i<MS.size(); i++)
				{
					mas[i] = MS[i].t;
					C[i] = MS[i].c;
				}
			}
		}
		
		// get sample
		vector<double> GetSample(bool WithoutCnsoredObservations=false)
		{
			if( WithoutCnsoredObservations == false )
				return mas;
			else
			{
				vector<double> r;
				for(int i=0; i<mas.size(); i++)
					if( C[i]==0 )
						r.push_back( mas[i] );
				return r;
			}
		}
		
		// get sample size
		int N()
		{
			return mas.size();
		}
		
		// Save selection to file for ISW Software
		void OutToISW(char *name_file)
		{
			if( this->isCensored==false )
			{
				FILE *ou = fopen(name_file,"w");
				fprintf(ou,"%s\n0 %d\n\n",Information,mas.size());
				for(unsigned int i=0; i<mas.size(); i++)
					fprintf(ou,"%.15lf\n",mas[i]);
				fclose(ou);
			}
		}

		// right censoring of the first type of sample
		void CensoredTypeFirst(double CensoredPoint)
		{
			if( this->isCensored == false )
			{
				this->isCensored = true;

				PracticeCensoredPercent = 0;
				for(unsigned int i=0; i<mas.size(); i++)
				{
					if( mas[i] > CensoredPoint )
					{
						C[i] = 1.0;
						PracticeCensoredPercent++;
					}
				}
				PracticeCensoredPercent = 100.0*PracticeCensoredPercent/mas.size();
				SortSample();
			}
		}

		// right censoring of the second type of sample
		void CensoredTypeSecond(int CensoredPercent)
		{
			if( this->isCensored == false )
			{
				this->isCensored = true;

				SortSample();
				if( CensoredPercent>=0 && CensoredPercent<100 )
				{
					int Count = double( CensoredPercent*mas.size() )/100.0;
					PracticeCensoredPercent = 100.0*double(Count)/mas.size();

					for(int i=0; i<Count; i++)
						C[ mas.size()-(i+1) ] = 1;
				}
			}
		}

		// right censoring of the third type of sample
		void CensoredTypeThird(Distribution &FC, mt19937boost &Gw)
		{
			if( this->isCensored == false )
			{
				this->isCensored = true;

				vector<double> fc;
				Sample SFC(FC,mas.size(),Gw);
				fc = SFC.GetSample();
				for(unsigned int i=0; i<fc.size(); i++)
				{
					if( mas[i] > fc[i] )
					{
						mas[i] = fc[i];
						C[i] = 1;
						PracticeCensoredPercent++;
					}
				}
				PracticeCensoredPercent = 100.0*PracticeCensoredPercent/mas.size();
				SortSample();

			}
		}

		// find out the real degree of censorship
		double RealCensoredPercent()
		{
			int sum=0;
			for(unsigned int i=0; i<C.size(); i++)
			{
				if( C[i] )
					sum++;
			}
			return 100*sum/double( C.size() );
		}

		double MAX()
		{
			double max = -DBL_MAX;
			for(int i=0; i<mas.size(); i++)
				if( mas[i] > max )
					max = mas[i];
			return max;
		}

		double MIN()
		{
			double min = +DBL_MAX;
			for(int i=0; i<mas.size(); i++)
				if( mas[i] < min )
					min = mas[i];
			return min;
		}

		// Get selection information as a text string
		string GetSampleInformation()
		{
			string str = Information;
			return str;
		}
};

#endif
