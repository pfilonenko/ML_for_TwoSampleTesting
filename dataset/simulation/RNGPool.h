#ifndef RNGPool_H
#define RNGPool_H

#include"mt19937boost.h"

class RNGPool
{
	private:
		int Initializing;
		vector<mt19937boost> RNGmt19937;

	public:
		RNGPool()
		{
			int count = 1024;
			Initializing = 100;
			for(int i=0; i<count; i++)
				RNGmt19937.push_back( mt19937boost( Initializing + i ) );
		}

		double operator()(int num)
		{
			if( num < RNGmt19937.size() )
				return RNGmt19937[num].MT19937Uniform01();
			else
				return -1;
		}

		mt19937boost operator[](int num)
		{
			if( num < RNGmt19937.size() )
				return RNGmt19937[num];
			else
				return NULL;
		}
};

static RNGPool GwMT19937;

#endif
