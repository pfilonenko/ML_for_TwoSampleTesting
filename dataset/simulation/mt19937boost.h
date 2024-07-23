#ifndef mt19937boost_H
#define mt19937boost_H

#include <ctime>
#include <iostream>
#include <vector>
#include <boost/random.hpp>
#include <boost/math/distributions/uniform.hpp>

using namespace std;
using namespace boost;

class mt19937boost
{
	private:
		mt19937 *rng;
		boost::random::uniform_01<double>u01;

	public:
		mt19937boost()
		{
			rng = NULL;
			Seed( 100 );
		}

		mt19937boost(unsigned int pt)
		{
			rng = NULL;
			Seed( pt );
		}
		
		void Seed(unsigned int pt)
		{
			if( rng != NULL )
				delete [] rng;
			
			rng = new mt19937(pt);
		}

		double MT19937Uniform01()
		{
			variate_generator<mt19937&, boost::random::uniform_01<double> >  uniform01_sampler(*rng, u01);
			return uniform01_sampler();
		}
};

#endif
