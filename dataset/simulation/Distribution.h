#ifndef Distribution_H
#define Distribution_H

#include<math.h>

#include<boost/random.hpp>
#include<boost/math/distributions/normal.hpp>
#include<boost/math/distributions/exponential.hpp>
#include<boost/math/distributions/uniform.hpp>
#include<boost/math/distributions/laplace.hpp>
#include<boost/math/distributions/lognormal.hpp>
#include<boost/math/distributions/cauchy.hpp>
#include<boost/math/distributions/logistic.hpp>
#include<boost/math/distributions/weibull.hpp>
#include<boost/math/distributions/gamma.hpp>
#include<boost/math/distributions/chi_squared.hpp>
#include<boost/math/distributions/non_central_chi_squared.hpp>
#include<boost/math/distributions/students_t.hpp>
#include<boost/math/distributions/rayleigh.hpp>
#include<boost/math/distributions/triangular.hpp>
#include<boost/math/distributions/beta.hpp>

#include <boost/math/special_functions/erf.hpp>

using namespace std;
using namespace boost;

class Distribution
{
	protected:
		double shift;
		double scale;
		char TitleParameters[1024];

	public:
		virtual double CDF(double x)=0;
		
		virtual double Mean()=0;
		virtual double Variance()=0;
		
		virtual double Quantile(double p)=0;
		double Median()
		{
			return Quantile(0.5);
		}

		void GetDistributionInformation(char buf[])
		{
			strcpy(buf,this->TitleParameters);
		}

		// change the value of the shift parameter
		void ChangeShift(double NewShift)
		{
			this->shift = NewShift;
		}

		// change the value of the scale parameter
		void ChangeScale(double NewScale)
		{
			if(NewScale > 0.0)
				this->scale = NewScale;
			else
				this->scale = 1.0e-5;
		}

		double GetShift()
		{
			return this->shift;
		}

		double GetScale()
		{
			return this->scale;
		}

		virtual double GetShape()=0;
		virtual void ChangeShape(double NewShape)=0;
};

//CRV - continuous random variable

//Normal distribution N( mean, sigma^2 )
class CRVNormal : public Distribution
{
	private:
	public:
		CRVNormal(double mean, double scale)
		{
			this->shift = mean;
			//this->scale = scale;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;

			sprintf(this->TitleParameters,"Gaussian distribution [mean=%lf, scale=%lf]",mean,scale);
		}

		double CDF(double x)
		{
			boost::math::normal_distribution<double> norm_dist(this->shift, this->scale);
			return cdf(norm_dist, x);
		}

		double Mean()
		{
			return this->shift;
		}

		double Variance()
		{
			return pow(this->scale,2.0);
		}

		double Quantile(double p)
		{
			boost::math::normal_distribution<double> norm_dist(this->shift, this->scale);
			return quantile(norm_dist, p);
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

//Exponential distribution F(x) = 1 - exp{ -scale*(x-shift) }
class CRVExponential : public Distribution
{
	private:
	public:
		CRVExponential(double shift, double scale)
		{
			this->shift = shift;
			//this->scale = scale;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;

			sprintf(this->TitleParameters,"Exponential distribution [shift=%lf, scale=%lf]",shift,scale);
		}
		
		double CDF(double x)
		{
			if( x-shift <= 0.0 )
				return 0.0;
			else
				return 1.0 - exp( scale*(-x+shift) );
				//return 1.0 - exp( -scale*(x+shift) );
		}

		double Mean()
		{
			return (1.0/this->scale) + shift;
		}

		double Variance()
		{
			return 1.0/pow(this->scale,2.0);
		}

		double Quantile(double p)
		{
			boost::math::exponential_distribution<double> exp_dist(this->scale);
			return (quantile(exp_dist, p) + shift);
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVUniform : public Distribution
{
	private:
		double a,b;

	public:
		CRVUniform(double a, double b)
		{
			this->a = min(a,b);
			this->b = max(a,b);

			sprintf(this->TitleParameters,"Uniform distribution [%lf; %lf]",a,b);
		}
		
		double CDF(double x)
		{
			boost::math::uniform_distribution<double> u(a,b);
			return cdf(u,x);
		}

		double Mean()
		{
			return (a+b)/2.0;
		}

		double Variance()
		{
			return pow(b-a,2)/12.0;
		}

		double Quantile(double p)
		{
			boost::math::uniform_distribution<double> u(a,b);
			return boost::math::quantile(u,p);
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVLaplace : public Distribution
{
	private:
	public:
		CRVLaplace(double shift, double scale)
		{
			this->shift = shift;
			//this->scale = scale;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;

			sprintf(this->TitleParameters,"Laplace distribution [shift=%lf, scale=%lf]",shift,scale);
		}
		
		double CDF(double x)
		{
			boost::math::laplace_distribution<double> lap(shift,scale);
			return boost::math::cdf(lap,x);
		}

		double Mean()
		{
			boost::math::laplace_distribution<double> lap(shift,scale);
			return boost::math::mean(lap);
		}

		double Variance()
		{
			boost::math::laplace_distribution<double> lap(shift,scale);
			return boost::math::variance(lap);
		}

		double Quantile(double p)
		{
			boost::math::laplace_distribution<double> lap(shift,scale);
			return boost::math::quantile(lap,p);
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVLogNormal : public Distribution
{
	private:
	public:
		CRVLogNormal(double shift, double scale)
		{
			this->shift = shift;
			//this->scale = scale;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;

			sprintf(this->TitleParameters,"LogNormal distribution [shift=%lf, scale=%lf]",shift,scale);
		}
		
		double CDF(double x)
		{
			boost::math::lognormal_distribution<double> lgn(shift,scale);
			return boost::math::cdf(lgn,x);
		}

		double Mean()
		{
			boost::math::lognormal_distribution<double> lgn(shift,scale);
			return boost::math::mean(lgn);
		}

		double Variance()
		{
			boost::math::lognormal_distribution<double> lgn(shift,scale);
			return boost::math::variance(lgn);
		}

		double Quantile(double p)
		{
			boost::math::lognormal_distribution<double> lgn(shift,scale);
			return boost::math::quantile(lgn,p);
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVCauchy : public Distribution
{
	private:
	public:
		CRVCauchy(double shift, double scale)
		{
			this->shift = shift;
			//this->scale = scale;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;

			sprintf(this->TitleParameters,"Cauchy distribution [shift=%lf, scale=%lf]",shift,scale);
		}
		
		double CDF(double x)
		{
			boost::math::cauchy_distribution<double> Cau(shift,scale);
			return boost::math::cdf(Cau,x);
		}

		double Mean()
		{
			return DBL_MAX;
		}

		double Variance()
		{
			return DBL_MAX;
		}

		double Quantile(double p)
		{
			boost::math::cauchy_distribution<double> Cau(shift,scale);
			return boost::math::quantile(Cau,p);
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVLogistic : public Distribution
{
	private:
	public:
		CRVLogistic(double shift, double scale)
		{
			this->shift = shift;
			//this->scale = scale;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;

			sprintf(this->TitleParameters,"Logistic distribution [shift=%lf, scale=%lf]",shift,scale);
		}
		
		double CDF(double x)
		{
			boost::math::logistic_distribution<double> log(shift,scale);
			return boost::math::cdf(log,x);
		}

		double Mean()
		{
			boost::math::logistic_distribution<double> log(shift,scale);
			return boost::math::mean(log);
		}

		double Variance()
		{
			boost::math::logistic_distribution<double> log(shift,scale);
			return boost::math::variance(log);
		}

		double Quantile(double p)
		{
			boost::math::logistic_distribution<double> log(shift,scale);
			return boost::math::quantile(log,p);
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVWeibull : public Distribution
{
	private:
		double shape;

	public:
		CRVWeibull(double shift, double scale, double shape)
		{
			this->shift = shift;
			//this->scale = scale;
			this->scale = ( scale <= 0.0 ) ? 1.0e-5 : scale;
			//this->shape = shape;
			this->shape = ( shape <= 0.0 ) ? 1.0e-5 : shape;

			sprintf(this->TitleParameters,"Weibull distribution [shift=%lf, scale=%lf, shape=%lf]",shift,scale,shape);
		}
		
		double CDF(double x)
		{
			double t = x - shift;
			if( t<=0 )
				return 0.0;
			else
			{
				boost::math::weibull_distribution<double> we(shape,scale);
				return boost::math::cdf(we,t);
			}
		}

		double Mean()
		{
			boost::math::weibull_distribution<double> we(shape,scale);
			return boost::math::mean(we)+shift;
		}

		double Variance()
		{
			boost::math::weibull_distribution<double> we(shape,scale);
			return boost::math::variance(we);
		}

		double Quantile(double p)
		{
			boost::math::weibull_distribution<double> we(shape,scale);
			return boost::math::quantile(we,p)+shift;
		}

		double GetShape()
		{
			return this->shape;
		}

		void ChangeShape(double NewShape)
		{
			if( NewShape > 0.0)
				this->shape = NewShape;
			else
				this->shape = 1.0e-5;
		}
};

class CRVGeneralizedWeibull : public Distribution
{
	private:
		double shape;

	public:
		CRVGeneralizedWeibull()
		{
			//this->shift = shift;
			//this->scale = scale;
			//this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;
			//this->shape = shape;

			//sprintf(this->TitleParameters,"Weibull distribution [shift=%lf, scale=%lf, shape=%lf]",shift,scale,shape);

			sprintf(this->TitleParameters,"Generalized Weibull distribution");
		}
		
		double CDF(double x)
		{
			return DBL_MAX;
		}

		double Mean()
		{
			return DBL_MAX;
		}

		double Variance()
		{
			return DBL_MAX;
		}

		double Quantile(double p)
		{
			return pow( pow( 1 - log(1.0-p) , 1/0.85 ) - 1.0 , 0.95 );
		}

		double GetShape()
		{
			return this->shape;
		}

		void ChangeShape(double NewShape)
		{
			if( NewShape > 0.0)
				this->shape = NewShape;
			else
				this->shape = 1.0e-5;
		}
};

class CRVGamma  : public Distribution
{
	private:
		double shape;

	public:
		CRVGamma(double shift, double scale, double shape)
		{
			this->shift = shift;
			//this->scale = scale;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;
			//this->shape = shape;
			this->shape = ( shape <= 0.0) ? 1.0e-5 : shape;

			sprintf(this->TitleParameters,"Gamma distribution [shift=%lf, scale=%lf, shape=%lf]",shift,scale,shape);
		}
		
		double CDF(double x)
		{
			if( x-shift < 0 )
				return 0.0;
			else
			{
				boost::math::gamma_distribution<double> G(shape,scale);
				return boost::math::cdf(G,x-shift);
			}
		}

		double Mean()
		{
			boost::math::gamma_distribution<double> G(shape,scale);
			return boost::math::mean(G)+shift;
		}

		double Variance()
		{
			boost::math::gamma_distribution<double> G(shape,scale);
			return boost::math::variance(G);
		}

		double Quantile(double p)
		{
			boost::math::gamma_distribution<double> G(shape,scale);
			return boost::math::quantile(G,p)+shift;
		}

		double GetShape()
		{
			return this->shape;
		}

		void ChangeShape(double NewShape)
		{
			if( NewShape > 0.0)
				this->shape = NewShape;
			else
				this->shape = 1.0e-5;
		}
};

class CRVChiSquare  : public Distribution
{
	private:
		double shape;

	public:
		CRVChiSquare(double shift, double shape)
		{
			this->shift = shift;
			this->scale = 0.0;
			//this->shape = shape;
			this->shape = ( shape <= 0.0) ? 1.0e-5 : shape;

			sprintf(this->TitleParameters,"Chi Square distribution [shift=%lf, shape=%lf]",shift,shape);
		}
		
		double CDF(double x)
		{
			boost::math::chi_squared_distribution<double> Chi(shape);
			return boost::math::cdf(Chi, x-shift);
		}

		double Mean()
		{
			boost::math::chi_squared_distribution<double> Chi(shape);
			return boost::math::mean(Chi)+shift;
		}

		double Variance()
		{
			boost::math::chi_squared_distribution<double> Chi(shape);
			return boost::math::variance(Chi);
		}

		double Quantile(double p)
		{
			boost::math::chi_squared_distribution<double> Chi(shape);
			return boost::math::quantile(Chi,p)+shift;
		}

		double GetShape()
		{
			return this->shape;
		}

		void ChangeShape(double NewShape)
		{
			if( NewShape > 0.0)
				this->shape = NewShape;
			else
				this->shape = 1.0e-5;
		}
};

class CRVStudent  : public Distribution
{
	private:
		double shape;

	public:
		CRVStudent(double shape)
		{
			//this->shape = shape;
			this->shape = ( shape <= 0.0) ? 1.0e-5 : shape;

			sprintf(this->TitleParameters,"Student distribution [shape=%lf]",shape);
		}
		
		double CDF(double x)
		{
			boost::math::students_t_distribution<double> t(shape);
			return cdf(t,x);
		}

		double Mean()
		{
			boost::math::students_t_distribution<double> t(shape);
			return mean(t);
		}

		double Variance()
		{
			boost::math::students_t_distribution<double> t(shape);
			return variance(t);
		}

		double Quantile(double p)
		{
			boost::math::students_t_distribution<double> t(shape);
			return quantile(t,p);
		}

		double GetShape()
		{
			return this->shape;
		}

		void ChangeShape(double NewShape)
		{
			if( NewShape > 0.0)
				this->shape = NewShape;
			else
				this->shape = 1.0e-5;
		}
};

class CRV_a1  : public Distribution
{
	private:
	public:
		CRV_a1()
		{
			sprintf(this->TitleParameters,"a1 distribution");
		}
		
		double CDF(double x)
		{
			return 0;
		}

		double Mean()
		{
			return 0.0;
		}

		double Variance()
		{
			return 0.0;
		}

		double Quantile(double p)
		{
			return 0.0;
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRV_a2  : public Distribution
{
	private:
	public:
		CRV_a2()
		{
			sprintf(this->TitleParameters,"a2 distribution");
		}
		
		double CDF(double x)
		{
			return 0;
		}

		double Mean()
		{
			return 0.0;
		}

		double Variance()
		{
			return 0.0;
		}

		double Quantile(double p)
		{
			return 0.0;
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVKolmogorov : public Distribution
{
	private:
		double CDFp(double x, double p)
		{
			return CDF(x) - p;
		}

	public:
		CRVKolmogorov()
		{
			sprintf(this->TitleParameters,"Kolmogorov distribution");
		}
		
		double CDF(double x)
		{
			if( x > 0.0 && x*x > DBL_EPSILON )
			{
				double sum1 = 0, sum2 = 0;
				double t = DBL_MAX;
				for(int k=0; k<INT_MAX && fabs(t)>DBL_EPSILON; k++)
				{
					t = pow(-1.0,k)*exp( -2.0*k*k*x*x );
					sum1 += t;
				}

				t = DBL_MAX;
				for(int k=-1; k>-INT_MAX && fabs(t)>DBL_EPSILON; k--)
				{
					t = pow(-1.0,k)*exp( -2.0*k*k*x*x );
					sum2 += t;
				}

				return sum1+sum2;
			}
			else
				return 0.0;
		}

		double Mean()
		{
			return DBL_MAX;
		}

		double Variance()
		{
			return DBL_MAX;
		}

		double Quantile(double p)
		{
			double a,b,c,pa,pb,pc;
			if( p<DBL_EPSILON || p>=1.0 )
				return DBL_MAX;
			else
			{
				a = 1.0e-5; b = 10;
				do
				{
					c = (a+b)/2.0;
					pa = CDF(a);	pb = CDF(b);	pc = CDF(c);
					if( pa<=p && p<=pc )
						b = c;
					else
						a = c;
				}
				while( fabs(b-a)>DBL_EPSILON );
			}
			return b;
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVRayleigh  : public Distribution
{
	public:
		CRVRayleigh(double shift, double scale)
		{
			this->shift = shift;
			this->scale = (scale <= 0.0 ) ? 1.0e-5 : scale;

			sprintf(this->TitleParameters,"Rayleigh distribution [shift=%lf, scale=%lf]",shift,scale);
		}
		
		double CDF(double x)
		{
			if( x-shift < 0 )
				return 0.0;
			else
			{
				boost::math::rayleigh_distribution<double> G( scale );
				return boost::math::cdf(G,x-shift);
			}
		}

		double Mean()
		{
			boost::math::rayleigh_distribution<double> G( scale );
			return boost::math::mean(G)+shift;
		}

		double Variance()
		{
			boost::math::rayleigh_distribution<double> G( scale );
			return boost::math::variance(G);
		}

		double Quantile(double p)
		{
			boost::math::rayleigh_distribution<double> G( scale );
			return boost::math::quantile(G,p)+shift;
		}

		double GetShape()
		{
			return 0.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVTriangular : public Distribution
{
	private:
		double Lower, Mode, Upper;

	public:
		CRVTriangular(double lower, double mode, double upper)
		{
			Lower = lower;
			Mode = mode;
			Upper = upper;

			boost::math::triangular_distribution<double> Tr(Lower, Mode, Upper);

			this->shift = this->Mean();
			this->scale = sqrt( this->Variance() );

			sprintf(this->TitleParameters,"Triangular distribution [lower=%lf, mode=%lf, upper=%lf]", lower, mode, upper);
		}
		
		double CDF(double x)
		{
			if( x < Lower )
				return 0;
			else
			{
				if( x > Upper )
					return 1;
				else
				{
					boost::math::triangular_distribution<double> Tr(Lower, Mode, Upper);
					return boost::math::cdf(Tr,x);
				}
			}
		}

		double Mean()
		{
			boost::math::triangular_distribution<double> Tr(Lower, Mode, Upper);
			return boost::math::mean(Tr);
		}

		double Variance()
		{
			boost::math::triangular_distribution<double> Tr(Lower, Mode, Upper);
			return boost::math::variance(Tr);
		}

		double Quantile(double p)
		{
			boost::math::triangular_distribution<double> Tr(Lower, Mode, Upper);
			return boost::math::quantile(Tr,p);
		}

		double GetShape()
		{
			return 1.0;
		}

		void ChangeShape(double NewShape)
		{
		}
};

class CRVBeta : public Distribution
{
	private:
		double shape;

	public:
		CRVBeta(double shift, double scale, double shape)
		{
			this->shift = shift;
			this->scale = ( scale <= 0.0 ) ? 1.0e-5 : scale;
			this->shape = ( shape <= 0.0 ) ? 1.0e-5 : shape;

			sprintf(this->TitleParameters,"Beta distribution [shift=%lf, shape1=%lf, shape2=%lf]",shift,scale,shape);
		}
		
		double CDF(double x)
		{
			double t = x;
			if( t<=0 || t>=1 )
				return 0.0;
			else
			{
				boost::math::beta_distribution<double> bt(scale, shape);
				return boost::math::cdf(bt,t);
			}
		}

		double Mean()
		{
			boost::math::beta_distribution<double> bt(scale, shape);
			return boost::math::mean(bt);
		}

		double Variance()
		{
			boost::math::beta_distribution<double> bt(scale, shape);
			return boost::math::variance(bt);
		}

		double Quantile(double p)
		{
			boost::math::beta_distribution<double> bt(scale, shape);
			return boost::math::quantile(bt,p);
		}

		double GetShape()
		{
			return this->shape;
		}

		void ChangeShape(double NewShape)
		{
			if( NewShape > 0.0)
				this->shape = NewShape;
			else
				this->shape = 1.0e-5;
		}
};

class CRVBetaIII : public Distribution
{
	private:
		double shape;

		double g(double x, double b)
		{
			return b*x/( 1.0+(b-1)*x );
		}

	public:
		CRVBetaIII(double shift, double scale, double shape)
		{
			this->shift = ( shift <= 0.0 ) ? 1.0e-5 : shift;
			this->scale = ( scale <= 0.0 ) ? 1.0e-5 : scale;
			this->shape = ( shape <= 0.0 ) ? 1.0e-5 : shape;

			sprintf(this->TitleParameters,"Beta-III distribution [shift=%lf, shape1=%lf, shape2=%lf]",shift,scale,shape);
		}
		
		double CDF(double x)
		{
			double t = x;
			if( t <= 0 )
				return 0.0;
			else
				if( t >= 1 )
					return 1.0;
			else
			{
				double a = shift;
				double b = scale;
				double c = shape;

				return boost::math::ibeta( b, c, g(x,a) );
			}
		}

		double Mean()
		{
			return 0.0;
		}

		double Variance()
		{
			return 0.0;
		}

		double Quantile(double p)
		{
			return 0.0;
		}

		double GetShape()
		{
			return this->shape;
		}

		void ChangeShape(double NewShape)
		{
			if( NewShape > 0.0)
				this->shape = NewShape;
			else
				this->shape = 1.0e-5;
		}
};

#endif
