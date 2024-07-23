#include"NelsonAalenSurvivalEstimate.h"

char *NelsonAalenSurvivalEstimate::getEstimateTitle()
{
	return "NelsonAalenSurvivalEstimate";
}

// calculating probability at a point
double NelsonAalenSurvivalEstimate::Probability(double t)
{
	int i;
	if( t < X[0] )
		return 1.0;
	else
		if( t > X[X.size()-1] )
		{
			if( CensoredLast==true )
				return F[F.size()-1];
			else
				return 0;
		}
		else
		{
			for(i=0; i<X.size() && t>X[i]; i++);

			if( fabs(X[i]-t)<DBL_EPSILON )
			{
				return F[i];
			}
			else
				return F[i-1];
		}
}

// quantile calculation
double NelsonAalenSurvivalEstimate::Quantile(double alpha)
{
	int i;
	double a,b;
	
	if( alpha < 0.0+DBL_EPSILON || alpha > 1.0-DBL_EPSILON )
		return -DBL_MAX;
	else
	{
		if( CensoredLast==true && alpha < F[F.size()-1] )
			return -DBL_MAX;
		else
		{
			if( alpha<F[F.size()-1] )	/////////
				return X[X.size()-1];	/////////

			a = 1.0;	b = F[0];
			for(i=0; i<F.size()+1; i++)
			{
				if( i > 0 )
				{
					a = b;
					b = i==F.size() ? 0.0 : F[i];
				}
				if( a > alpha && alpha >= b )
					break;
			}
			return X[i];
		}
	}
}

// constructor
NelsonAalenSurvivalEstimate::NelsonAalenSurvivalEstimate(Sample &s)
{
	s.SortSample();

	int n = s.N();
	CensoredLast = ( s._C( s.N()-1 )==1? true : false );
	double t;
	
	X.resize( n );
	F.resize( n );

	int i;
	double lambda_new,lambda_last,Y,N,n_last,n_new;

	Y = N = n_last = n_new = 0;
	lambda_new = lambda_last = 0.0;
	for(i=0; i<n; i++)
	{
		t = s._X(i);
		X[i] = t;

		// вычисление У и N
		if( s._C(i)==0 )
			n_new += 1;
		Y = n-i;
            
        lambda_new = lambda_last + double(n_new - n_last)/double(Y);

		F[i] = exp( -lambda_new );

		if( s._C(i)==0 )
			n_last = n_new;
        lambda_last = lambda_new;
	}
}

// destructor
NelsonAalenSurvivalEstimate::~NelsonAalenSurvivalEstimate()
{
}
