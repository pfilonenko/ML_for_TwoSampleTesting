#ifndef ContinuousSurvivalEstimate_H
#define ContinuousSurvivalEstimate_H

#include"AdbushukurovEstimate.h"

class ContinuousSurvivalEstimate
{
	private:
		BreslowEstimate *F;

		//Hermite interpolation spline class
		class HermiteInterpolationSpline
		{
			private:
				struct SplineStruct
				{
					double x,f; 

					bool operator <(SplineStruct &A)
					{
						if( this->x < A.x )
							return true;
						else
							return false;
					}
				};
				vector<SplineStruct> T;

				double Derivate(int i)
				{
					double res;
					double pb, p, ps;
					double tb, t, ts;

					if( i+1 == T.size()  )
					{
						pb = 0.0;
						tb = T[T.size()-1].x + (T[T.size()-1].x - T[0].x);
					}
					else
					{
						pb = T[i+1].f;
						tb = T[i+1].x;
					}

					p  = T[i].f;
					t  = T[i].x;

					if( i-1 < 0 )
					{
						ps = 1.0;
						ts = T[0].x - (T[T.size()-1].x - T[0].x);
					}
					else
					{
						ps = T[i-1].f;
						ts = T[i-1].x;
					}

					res = (pb - p)/(2.0*(tb - t)) + (p - ps)/(2.0*(t - ts));
					return res;
				}

				//function that regularizes a spline so that it is monotonically decreasing
				void Monotonicity(double xk, double xk1, double pk, double pk1, double hk, double &mk, double &mk1)
				{
					double eps = 1.0e-10;
					double A,B,C,Dsk,t1,t2;
					bool P = true;
					
					do{

						A = 3*(2*pk + hk*mk - 2*pk1 + hk*mk1);
						B = 2*(-3*pk - 2*hk*mk + 3*pk1 - hk*mk1);
						C = hk*mk;

						Dsk = B*B - 4*A*C;
						if( Dsk < 0.0 )
							P = false;
						else
						{
							t1 = (-B - sqrt(Dsk))/(2.0*A);
							t2 = (-B + sqrt(Dsk))/(2.0*A);

							t1 = xk + t1*hk;
							t2 = xk + t2*hk;
							if( (xk <= t1 && t1 <= xk1) || (xk <= t2 && t2 <= xk1) )
							{
								if( fabs(mk) > eps )
									mk /= 2.0;
								if( fabs(mk1) > eps )
									mk1 /= 2.0;
							}
							else
							{
								P = false;
							}
						}
					}
					while( P && (fabs(mk)>eps || fabs(mk1)>eps) );
				}

				double FunctionCalculation(int i, double x)
				{
					double pk,pk1,mk,mk1,hk,t,xk,xk1;

					pk = T[i].f;
					pk1 = T[i+1].f;
					hk = T[i+1].x - T[i].x;
					xk = T[i].x;
					xk1 = T[i+1].x;

					t = (x - T[i].x)/hk;

					mk = Derivate(i);
					mk1 = Derivate(i+1);
					
					Monotonicity(xk,xk1,pk,pk1,hk,mk,mk1);

					double phi1 = 2*pow(t,3) - 3*pow(t,2) + 1;
					double phi2 = pow(t,3) - 2*pow(t,2) + t;
					double phi3 = -2*pow(t,3) + 3*pow(t,2);
					double phi4 = pow(t,3) - pow(t,2);

					return phi1*pk + phi2*mk*hk + phi3*pk1 + phi4*mk1*hk;
				}

			public:
				HermiteInterpolationSpline(vector<double> &x, vector<double> &f, double dfdx_0=1.0, double dfdx_n=1.0)
				{
					if( x.size()==f.size() )
					{
						for(int i=0; i<x.size(); i++)
						{
							SplineStruct Temp;
							Temp.x = x[i];
							Temp.f = f[i];
							T.push_back( Temp );
						}
						sort(T.begin(),T.end());
					}
				}

				double Function(double x)
				{
					if( x < T[0].x || x > T[T.size()-1].x )
						return 0.0;
					else
					{
						for(int i=0; i<T.size()-1; i++)
							if( x >= T[i].x && x <= T[i+1].x )
								return FunctionCalculation(i,x);
					}
				}
		} *Sp;

		// parameters of the “tail” of the distribution, specified as a hyporebola A/(t - B)
		double A,B;

		// other variables necessary to calculate the Probability and Quantile functions
		double StartofHermiteSpline;	// the point from which the Hermite spline begins
		double EndOfHermiteSpline;	// the point at which the Hermite spline ends and the hyperbola begins

	public:
		ContinuousSurvivalEstimate(Sample &S, double EPS = 0.0)
		{
			S.SortSample();
			F = new BreslowEstimate(S);

			vector<double> mas,x,f;
			mas = S.GetSample();

			// start of spline
			this->StartofHermiteSpline = mas[0];
			x.push_back( this->StartofHermiteSpline );
			f.push_back( 1.0 );

			// forming spline points
			double last = 1.0;
			for(int i=0; i<mas.size()-1; i++)
			{
				double t = (mas[i]+mas[i+1])/2.0;
				double ft = F->Probability(t);

				// if two steps differ significantly, then two different observations
				if( fabs(ft-last) > EPS )
				{
					x.push_back( t );
					f.push_back( ft );
					last = ft;
				}
				else
				{
					x[x.size()-1] = (x[x.size()-1] + t)/2.0;
					f[f.size()-1] = (f[f.size()-1] + ft)/2.0;
				}
			}

			this->EndOfHermiteSpline = x[ x.size()-1 ];

			if( fabs(f[0]-1.0)>1.0e-10 )
			{
				x.push_back( this->StartofHermiteSpline );
				f.push_back( 1.0 );
			}
			else
				x[0] = this->StartofHermiteSpline;

			// constructing a Hermite spline
			Sp = new HermiteInterpolationSpline(x,f);

			// formation of the right tail of the distribution in the form of a hyperbola
			double x0,x1,y0,y1,M;

			x0 = this->EndOfHermiteSpline;
			y0 = this->Probability(x0);
			M = (this->Probability( x0 ) - this->Probability( x0-1.0e-10 ))/1.0e-10;

			A = y0/exp(M*x0/y0);
			B = -M/y0;
		}

		double Probability(double x)
		{
			// if to spline
			if( x < StartofHermiteSpline )
				return 1.0;
			else
				// if hyperbole
				if( x > EndOfHermiteSpline )
					return A*exp( -B*x );
				else
					// if the spline value
					return Sp->Function(x);
		}

		double Quantile(double alpha)
		{
			if( alpha <= 0.0 )
				return +DBL_MAX;
			else
				if( alpha >= 1.0 )
					return -DBL_MAX;
				else
					// if the quantile is needed in the hyperbola region
					if( alpha < Sp->Function(this->EndOfHermiteSpline) )
					{
						// then according to the hyperbole the quantile is considered
						return exp(-log(alpha/A)/B);
					}
					else
					{
						// then the quantile is calculated using a spline
						double a, b, c, fa, fb, fc;
						a = this->StartofHermiteSpline;
						b = this->EndOfHermiteSpline;
						fa = Sp->Function(a);
						fb = Sp->Function(b);
						do{
							c = (a + b)/2.0;
							fc = Sp->Function(c);
							if( fa >= alpha && alpha >= fc )
							{
								b = c;
								fb = fc;
							}
							else
							{
								a = c;
								fa = fc;
							}
						}
						while( fabs(fc-alpha)>1.0e-10 && fabs(fa-fb)>1.0e-10 );
						return c;
					}
		}

		char *getEstimateTitle()
		{
			return "ContinuousSurvivalEstimate";
		}

		~ContinuousSurvivalEstimate()
		{
			delete F;
			delete Sp;
		}
};

#endif
