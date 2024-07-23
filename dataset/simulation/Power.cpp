#include"Power.h"

double Power::Value(double alfa)
{
	if(alfa>0.0 && alfa<1.0)
	{
		int sum = 0;
		double x1,x2;
		int kolH0 = H0.size();
		int kolH1 = H1.size();

		if( strcmp(TypeOfHypothesys,"right")==0 )
		{
			x1 = H0[ int(kolH0*(1.0-alfa)) ];
			for(int i=kolH1-1; i>=0 && H1[i] >= x1; --i)
				sum++;
			return double(sum)/double(kolH1);
		}

		if( strcmp(TypeOfHypothesys,"double")==0 )
		{
			alfa /= 2.0;	//cause the test has double critical area

			double res = 0.0;
			x1 = H0[ int(kolH0*(1.0-alfa))+1 ];
			x2 = H0[ int(kolH0*alfa)+1 ];

			for(int i=0; i<kolH1; i++)
			{
				if(H1[i] < x2)
					sum++;
				else
					break;
			}

			res += double(sum)/double(kolH1);

			sum = 0;
			for(int i=0; i<kolH1; i++)
			{
				if(H1[i] < x1)
					sum++;
				else
					break;
			}
			res += 1.0 - double(sum)/double(kolH1);

			return res;
		}

		if( strcmp(TypeOfHypothesys,"left")==0 )
		{
			x1 = H0[ int(kolH0*(1.0-alfa))+1 ];
			x2 = H0[ int(kolH0*alfa) ];

			for(int i=0; i<kolH1; i++)
			{
				if(H1[i] < x2)
					sum++;
				else
					break;
			}
			return double(sum)/double(kolH1);
		}
	}
	else
		return -DBL_EPSILON;
}

Power::Power(vector<double> &h0, vector<double> &h1, const char type[])
{
	if(type==NULL)
	{
		cout<< "Didn't specify type of criteria\n";
		exit(0);
	}

	strcpy(TypeOfHypothesys,type);

	this->H0 = h0;
	this->H1 = h1;

	sort(H0.begin(),H0.end());
	sort(H1.begin(),H1.end());
}

Power::Power(char *fn1, char *fn2, const char type[])
{
	if(type==NULL)
	{
		cout<< "Didn't specify type of criteria\n";
		exit(0);
	}

	strcpy(TypeOfHypothesys,type);
	int u;	char t;
	double temp;
	FILE *in1 = fopen(fn1,"r");
		fscanf(in1,"%c",&t);
		while(t != '\n')
			fscanf(in1,"%c",&t);
		fscanf(in1,"%d",&u);

		fscanf(in1,"%d",&u);
		H0.resize( u );
		for(int i=0; i<H0.size(); i++)
		{
			fscanf(in1,"%lf",&temp);
			H0[i] = temp;
		}
	fclose(in1);

	FILE *in2 = fopen(fn2,"r");
		fscanf(in2,"%c",&t);
		while(t != '\n')
			fscanf(in2,"%c",&t);
		fscanf(in2,"%d",&u);

		fscanf(in2,"%d",&u);
		H1.resize( u );
		for(int i=0; i<H1.size(); i++)
		{
			fscanf(in2,"%lf",&temp);
			H1[i] = temp;
		}
	fclose(in2);

	sort(H0.begin(),H0.end());
	sort(H1.begin(),H1.end());
}