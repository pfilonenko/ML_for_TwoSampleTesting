#ifndef AlternativeHypotheses_H
#define AlternativeHypotheses_H

#include"Sample.h"

class AlternativeHypotheses
{
	private:
		//List of Alternative Hypotheses

		void H1111(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.861128, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.350471, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.634900, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.185624, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.865510, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.100000, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.115575, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.543470, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.801210, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.336119, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.005152, 2.000000);
			}

		}

		void H1112(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.162377, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.236091, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.825753, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.581145, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.414217, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.100000, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.324015, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.350207, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.918747, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.661459, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.485753, 2.000000);
			}

		}

		void H1113(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.111089);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.249989);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.428563);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.666658);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.999990);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.100000, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.100027);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.222484);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.375865);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.573728);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.839031);
			}

		}

		void H1121(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 1.100000, 2.400000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.226038, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.170001, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.674401, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.358604, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.125202, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.370153);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.468127, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.337012, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.810199, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.478353, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.236919, 2.000000);
			}

		}

		void H1122(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 1.100000, 2.400000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.918436, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.205574, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.882825, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.684847, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.544487, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.370153);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.072968, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.309489, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.965080, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.754763, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.606491, 2.000000);
			}

		}

		void H1123(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 1.100000, 2.400000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.109186);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.234024);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.379281);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.552187);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.764410);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.370153);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.099145);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.211778);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.341763);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.494844);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.680078);
			}

		}

		void H1131(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.010000, 0.913000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.653627, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.353920, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.332441, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.721788, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.302618, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.742000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.203877, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.167737, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.203362, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.597872, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.166453, 2.000000);
			}

		}

		void H1132(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.010000, 0.913000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.188034, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.791105, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.202096, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.861957, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.635278, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.742000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.915521, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.665928, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.112872, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.783212, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.558243, 2.000000);
			}

		}

		void H1133(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.010000, 0.913000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.071393);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.164624);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.282039);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.433541);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.635369);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.742000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.082226);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.185410);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.317970);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.494657);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.741994);
			}

		}

		void H1211(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.060378, 1.160354);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.661571, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.883098, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.038609, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.505319, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.121965, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.863637);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.470775, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.721591, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.893038, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.372825, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.002168, 2.000000);
			}

		}

		void H1212(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.060378, 1.160354);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.629371, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.525493, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.034414, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.740001, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.537536, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.863637);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.503975, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.431263, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.956133, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.672903, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.479619, 2.000000);
			}

		}

		void H1213(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.060378, 1.160354);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.089602);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.199964);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.339386);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.521600);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.770809);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.863637);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.095891);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.215883);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.370119);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.575751);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.863629);
			}

		}

		void H1221(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.300000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 2.970124, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 1.808063, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.257619, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 0.912021, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.665779, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.900000, 1.100000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.284803, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.041926, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.449221, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.072967, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.810000, 2.000000);
			}

		}

		void H1222(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.300000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.663362, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 0.950844, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.635197, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.447036, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.318629, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.900000, 1.100000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.855560, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.080764, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.734915, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.526834, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.384000, 2.000000);
			}

		}

		void H1223(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.300000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.144434);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.324989);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.557131);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.866653);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.299983);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.900000, 1.100000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.126810);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.282417);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.478549);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.734445);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.084156);
			}

		}

		void H1231(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.861128, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.350471, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.634900, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.185624, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.865510, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.090000, 1.100000, 1.070000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.308087, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.693594, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.927320, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.443312, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.095328, 2.000000);
			}

		}

		void H1232(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.162377, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.236091, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.825753, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.581145, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.414217, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.090000, 1.100000, 1.070000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.444079, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.433947, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.983985, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.713930, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.528052, 2.000000);
			}

		}

		void H1233(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.111089);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.249989);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.428563);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.666658);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.999990);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.090000, 1.100000, 1.070000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.094352);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.208896);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.351230);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.533455);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.776116);
			}

		}

		void H1311(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.300000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 2.970124, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 1.808063, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.257619, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 0.912021, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.665779, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.806928, 1.064481);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.289883, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.016658, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.412808, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.032669, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.761000, 2.000000);
			}

		}

		void H1312(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.300000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.663362, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 0.950844, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.635197, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.447036, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.318629, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.806928, 1.064481);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.847971, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.063271, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.714954, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.506783, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.364000, 2.000000);
			}

		}

		void H1313(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.300000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.144434);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.324989);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.557131);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.866653);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.299983);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.806928, 1.064481);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.128951);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.289040);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.493304);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.763286);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.137415);
			}

		}

		void H1321(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.000000, 1.200000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.859651, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.203607, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.425259, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.933432, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.576652, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.567000, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.425745, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.501904, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.607265, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 2.049071, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.650478, 2.000000);
			}

		}

		void H1322(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.000000, 1.200000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.853326, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.764679, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.275763, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.979005, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.771498, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.567000, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.157758, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.917672, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.368492, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 1.038861, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.810972, 2.000000);
			}

		}

		void H1323(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.000000, 1.200000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.074294);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.160081);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.260849);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.381826);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.531330);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.567000, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.067750);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.147815);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.242844);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.358081);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.501851);
			}

		}

		void H1331(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.118000, 1.100000, 1.735000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.718416, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.471857, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.882826, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.506048, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.227556, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.010000, 0.600000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.166400, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.697198, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.013095, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.585166, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.277448, 2.000000);
			}

		}

		void H1332(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.118000, 1.100000, 1.735000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.189316, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.359773, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.984828, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.755408, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.593367, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.010000, 0.600000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.423724, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.476309, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.054341, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.800077, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.623433, 2.000000);
			}

		}

		void H1333(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.118000, 1.100000, 1.735000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.097386);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.209772);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.341895);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.500986);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.698802);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.010000, 0.600000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.089084);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.193345);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.317387);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.468256);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.657282);
			}

		}

		void H1411(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.861128, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.350471, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.634900, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.185624, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.865510, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.050000, 1.159526);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.456211, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.123002, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.492704, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.097460, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.752224, 2.000000);
			}

		}

		void H1412(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.162377, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.236091, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.825753, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.581145, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.414217, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.050000, 1.159526);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.944996, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.122660, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.758349, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.541159, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.355461, 2.000000);
			}

		}

		void H1413(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.111089);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.249989);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.428563);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.666658);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.999990);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.050000, 1.159526);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.121051);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.270408);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.459321);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.705980);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.041805);
			}

		}

		void H1421(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.273214, 1.475559);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 6.916350, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 4.368605, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 3.159060, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 2.390616, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.832533, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.159985, 1.300384, 1.273295);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 6.621223, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 4.181125, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 3.026665, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 2.297283, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.771426, 2.000000);
			}

		}

		void H1422(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.273214, 1.475559);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.948981, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 2.334542, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.615088, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 1.181061, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.879859, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.159985, 1.300384, 1.273295);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.783153, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 2.239920, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.553557, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 1.140912, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.855880, 2.000000);
			}

		}

		void H1423(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.273214, 1.475559);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.057728);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.128003);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.214658);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.324866);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.470925);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.159985, 1.300384, 1.273295);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.059721);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.132021);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.220689);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.332542);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.478981);
			}

		}

		void H1431(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.020000, 1.000000, 1.100000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.700784, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.307047, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.642971, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.221672, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.917279, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.909091);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.247234, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.585514, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.798388, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.304185, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.952060, 2.000000);
			}

		}

		void H1432(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.020000, 1.000000, 1.100000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.094067, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.223430, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.834831, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.601051, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.439680, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.909091);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.378686, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.359699, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.908327, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.639259, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.455638, 2.000000);
			}

		}

		void H1433(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.020000, 1.000000, 1.100000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.111603);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.247991);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.419016);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.640676);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.940913);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.909091);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.100964);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.227255);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.389602);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.606053);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.909083);
			}

		}

		void H1511(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.980290, 0.905449);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.053382, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.404159, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.632106, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.154884, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.821226, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.972861, 0.974537);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.673090, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.229340, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.545878, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.117277, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.818287, 2.000000);
			}

		}

		void H1512(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.980290, 0.905449);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.249548, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.256296, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.821286, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.565313, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.393318, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.972861, 0.974537);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.054497, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.171146, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.780174, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.547377, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.38849, 2.000000);
			}

		}

		void H1513(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.980290, 0.905449);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.109158);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.249115);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.433445);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.685697);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.049034);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.972861, 0.974537);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.117327);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.264458);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.454242);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.708239);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.065406);
			}

		}

		void H1521(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.861128, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.350471, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.634900, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.185624, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.865510, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.071424, 0.906609, 1.059531);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.566820, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.223768, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.587212, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.185658, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.897391, 2.000000);
			}

		}

		void H1522(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.162377, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.236091, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.825753, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.581145, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.414217, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.071424, 0.906609, 1.059531);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.021591, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.182849, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.809854, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.586274, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.376928, 2.000000);
			}

		}

		void H1523(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.111089);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.249989);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.428563);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.666658);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.999990);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.071424, 0.906609, 1.059531);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.114307);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.253602);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.427086);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.649745);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.947069);
			}

		}

		void H1531(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.010000, 1.000000, 1.150000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.387212, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.714433, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.920456, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.419320, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.059307, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.833333);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.633361, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.820557, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.961876, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.422747, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.038611, 2.000000);
			}

		}

		void H1532(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.010000, 1.000000, 1.150000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.475268, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.436889, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.975016, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.698194, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.507905, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.833333);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.595142, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.483312, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.990901, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.697373, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.497060, 2.000000);
			}

		}

		void H1533(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.010000, 1.000000, 1.150000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.095026);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.211913);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.359395);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.551800);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.814261);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.833333);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.092501);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.208298);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.357130);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.555548);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.833326);
			}

		}

		void H1611(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.968728, 1.214425);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.364138, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.129435, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.538755, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.160871, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.884580, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.107793);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 3.485434, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.121764, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.475819, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.070259, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 0.767139, 2.000000);
			}

		}

		void H1612(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.968728, 1.214425);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.916861, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.134860, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.783906, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.571283, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.423176, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.107793);
				if( percent==10 )
					D = new CRVGamma(0.000000, 1.951956, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.115816, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.745404, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.524597, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.371695, 2.000000);
			}

		}

		void H1613(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 0.968728, 1.214425);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.120293);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.265597);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.445595);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.675940);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.983904);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 1.107793);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.123076);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.276939);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.474759);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.738518);
				if( percent==50 )
					D = new CRVExponential(0.000000, 1.107781);
			}

		}

		void H1621(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.100000, 1.040952);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.398293, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.689530, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.879457, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.369962, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.005993, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.900000, 1.302500);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.378144, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 2.737644, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 1.957905, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.463845, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.106736, 2.000000);
			}

		}

		void H1622(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.100000, 1.040952);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.468080, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.416741, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.950447, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.672018, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.481581, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.900000, 1.302500);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.482599, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.455344, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 0.997059, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.721311, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.530759, 2.000000);
			}

		}

		void H1623(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.100000, 1.040952);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.096791);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.217333);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.371521);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.575931);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.860205);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 0.900000, 1.302500);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.093608);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.207637);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.350013);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.533590);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.780709);
			}

		}

		void H1631(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.100000, 1.100000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.362141, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.490936, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.611214, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 2.057207, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.657855, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.471274, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.132023, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.295988, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.437862, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.901759, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.519193, 2.000000);
			}

		}

		void H1632(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.100000, 1.100000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.123198, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.910091, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.367354, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 1.039462, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.811501, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.471274, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.971007, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.795985, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.274300, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.961311, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.745325, 2.000000);
			}

		}

		void H1633(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.100000, 1.100000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.068842);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.149050);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.244138);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.359407);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.503316);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.471274, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.072970);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.159069);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.261925);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.387542);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.545495);
			}

		}

		void H1711(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.948012);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.810137, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.407175, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.348738, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.720279, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.291690, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.173373, 1.325414, 0.911495);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.978414, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.608508, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.513621, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.839588, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.368746, 2.000000);
			}

		}

		void H1712(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.948012);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.269205, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.815704, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.208897, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.860697, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.630003, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.173373, 1.325414, 0.911495);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.367078, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.911752, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.282600, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.913158, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.664587, 2.000000);
			}

		}

		void H1713(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.948012);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.069769);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.162790);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.280702);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.433913);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.639512);
			}
			else
			{
				if( percent==0 )
					D = new CRVWeibull(0.173373, 1.325414, 0.911495);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.068622);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.156631);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.267773);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.412305);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.607408);
			}

		}

		void H1721(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.500000, 1.047995);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.024053, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.243256, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.409720, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.888519, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.516136, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.141079, 0.596104);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.733880, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.067239, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.291021, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.805309, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.455902, 2.000000);
			}

		}

		void H1722(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.500000, 1.047995);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.915154, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.771528, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.262222, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.956065, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.744382, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.141079, 0.596104);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.755302, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.679484, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.200214, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.911324, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.710552, 2.000000);
			}

		}

		void H1723(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.500000, 1.047995);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.074074);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.160787);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.263997);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.389539);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.546689);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.141079, 0.596104);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.078267);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.169858);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.278745);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.411087);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.576783);
			}

		}

		void H1731(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.000000, 1.200000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 4.859651, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.203607, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.425259, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.933432, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.576652, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.530778, 1.000000);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.314058, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.423822, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.543151, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.993409, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.600947, 2.000000);
			}

		}

		void H1732(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.000000, 1.200000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.853326, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.764679, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.275763, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.979005, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.771498, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.530778, 1.000000);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.086768, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.871547, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.332860, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 1.009575, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.786221, 2.000000);
			}

		}

		void H1733(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.500000, 1.000000, 1.200000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.074294);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.160081);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.260849);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.381826);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.531330);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.530778, 1.000000);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.069641);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.151882);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.249717);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.368655);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.517450);
			}

		}

		void H1811(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.916110);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.615548, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.328127, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.312709, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.706040, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.289843, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.010000, 1.213750, 1.192701);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.491611, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.408846, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.419961, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.795045, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.345251, 2.000000);
			}

		}

		void H1812(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.916110);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.165329, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.776955, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.191781, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.854027, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.629052, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.010000, 1.213750, 1.192701);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.104184, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.806911, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.229792, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.883505, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.645074, 2.000000);
			}

		}

		void H1813(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.916110);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.071974);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.166004);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.284517);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.437548);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.641554);
			}
			else
			{
				if( percent==0 )
					D = new CRVGamma(0.010000, 1.213750, 1.192701);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.075372);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.168045);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.284527);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.435879);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.641435);
			}

		}

		void H1821(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.817740);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.071034, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.099297, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.205902, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.662635, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.283453, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.185751, 0.818541);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.173981, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.224946, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.303556, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.726055, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.314931, 2.000000);
			}

		}

		void H1822(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.817740);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.880068, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.665670, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.141449, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.833889, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.625848, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.185751, 0.818541);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.932741, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.719286, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.180145, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.858106, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.637812, 2.000000);
			}

		}

		void H1823(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.817740);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.078325);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.175679);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.296169);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.448771);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.648143);
			}
			else
			{
				if( percent==0 )
					D = new CRVExponential(0.185751, 0.818541);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.078285);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.172961);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.290312);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.439843);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.637346);
			}

		}

		void H1831(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.010000, 1.697784, 1.846080);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.193419, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.445853, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.617824, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 2.086215, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.691366, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.293039, 0.569569);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.386966, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.510629, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.635536, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 2.086813, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.691079, 2.000000);
			}

		}

		void H1832(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.010000, 1.697784, 1.846080);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.050344, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.889040, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.363554, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 1.041520, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.813571, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.293039, 0.569569);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.145898, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.927239, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.383202, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 1.054535, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.825570, 2.000000);
			}

		}

		void H1833(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.010000, 1.697784, 1.846080);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.070562);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.152301);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.248853);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.365830);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.512486);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.293039, 0.569569);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.068103);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.147504);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.241487);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.355209);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.496931);
			}

		}

		void H1911(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 1.355236, 1.018477);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.173132, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.162643, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.208862, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.608583, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.179574, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.867936);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.338846, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.213279, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.259594, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.684689, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.286851, 2.000000);
			}

		}

		void H1912(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 1.355236, 1.018477);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.902912, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.665265, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.116474, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.788698, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.564465, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.867936);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.019416, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.720930, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.166668, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.844081, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.627535, 2.000000);
			}

		}

		void H1913(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVWeibull(0.000000, 1.355236, 1.018477);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.082283);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.185060);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.316581);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.491123);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.734274);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.867936);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.075171);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.170791);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.290249);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.443046);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.644727);
			}

		}

		void H1921(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.134293, 1.231701);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.254084, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.268369, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.324974, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.728124, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.297803, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.876612);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.387215, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.233565, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.269045, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.688521, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.287409, 2.000000);
			}

		}

		void H1922(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.134293, 1.231701);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.972222, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.733580, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.181922, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.850558, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.622087, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.876612);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.044775, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.730802, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.171125, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.845861, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.627816, 2.000000);
			}

		}

		void H1923(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVGamma(0.000000, 1.134293, 1.231701);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.078640);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.175066);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.296097);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.453126);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.666078);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.876612);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.074608);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.169936);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.289220);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.442055);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.644148);
			}

		}

		void H1931(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.744711);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.184921, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.156206, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.195341, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.592055, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.162207, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.866187);
				if( percent==10 )
					D = new CRVWeibull(0.000000, 5.329173, 2.000000);
				if( percent==20 )
					D = new CRVWeibull(0.000000, 3.209212, 2.000000);
				if( percent==30 )
					D = new CRVWeibull(0.000000, 2.257695, 2.000000);
				if( percent==40 )
					D = new CRVWeibull(0.000000, 1.683918, 2.000000);
				if( percent==50 )
					D = new CRVWeibull(0.000000, 1.286738, 2.000000);
			}

		}

		void H1932(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.744711);
				if( percent==10 )
					D = new CRVGamma(0.000000, 2.904860, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.659861, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.108821, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.780361, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.556211, 2.000000);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.866187);
				if( percent==10 )
					D = new CRVGamma(0.000000, 3.014351, 2.000000);
				if( percent==20 )
					D = new CRVGamma(0.000000, 1.718952, 2.000000);
				if( percent==30 )
					D = new CRVGamma(0.000000, 1.165773, 2.000000);
				if( percent==40 )
					D = new CRVGamma(0.000000, 0.843723, 2.000000);
				if( percent==50 )
					D = new CRVGamma(0.000000, 0.627478, 2.000000);
			}

		}

		void H1933(int num, int percent)
		{
			if( num==1 )
			{
				if( percent==0 )
					D = new CRVExponential(0.000000, 0.744711);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.082533);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.186091);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.319133);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.496464);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.744705);
			}
			else
			{
				if( percent==0 )
					D = new CRVLogNormal(0.000000, 0.866187);
				if( percent==10 )
					D = new CRVExponential(0.000000, 0.075284);
				if( percent==20 )
					D = new CRVExponential(0.000000, 0.170963);
				if( percent==30 )
					D = new CRVExponential(0.000000, 0.290457);
				if( percent==40 )
					D = new CRVExponential(0.000000, 0.443245);
				if( percent==50 )
					D = new CRVExponential(0.000000, 0.644845);
			}

		}

	public:
		AlternativeHypotheses(int H, int num, int percent)
		{
			D = NULL;

			switch( H )
			{				
				case 1111:
					H1111(num,percent);
					break;
				case 1112:
					H1112(num,percent);
					break;
				case 1113:
					H1113(num,percent);
					break;
				case 1121:
					H1121(num,percent);
					break;
				case 1122:
					H1122(num,percent);
					break;
				case 1123:
					H1123(num,percent);
					break;
				case 1131:
					H1131(num,percent);
					break;
				case 1132:
					H1132(num,percent);
					break;
				case 1133:
					H1133(num,percent);
					break;
				case 1211:
					H1211(num,percent);
					break;
				case 1212:
					H1212(num,percent);
					break;
				case 1213:
					H1213(num,percent);
					break;
				case 1221:
					H1221(num,percent);
					break;
				case 1222:
					H1222(num,percent);
					break;
				case 1223:
					H1223(num,percent);
					break;
				case 1231:
					H1231(num,percent);
					break;
				case 1232:
					H1232(num,percent);
					break;
				case 1233:
					H1233(num,percent);
					break;
				case 1311:
					H1311(num,percent);
					break;
				case 1312:
					H1312(num,percent);
					break;
				case 1313:
					H1313(num,percent);
					break;
				case 1321:
					H1321(num,percent);
					break;
				case 1322:
					H1322(num,percent);
					break;
				case 1323:
					H1323(num,percent);
					break;
				case 1331:
					H1331(num,percent);
					break;
				case 1332:
					H1332(num,percent);
					break;
				case 1333:
					H1333(num,percent);
					break;
				case 1411:
					H1411(num,percent);
					break;
				case 1412:
					H1412(num,percent);
					break;
				case 1413:
					H1413(num,percent);
					break;
				case 1421:
					H1421(num,percent);
					break;
				case 1422:
					H1422(num,percent);
					break;
				case 1423:
					H1423(num,percent);
					break;
				case 1431:
					H1431(num,percent);
					break;
				case 1432:
					H1432(num,percent);
					break;
				case 1433:
					H1433(num,percent);
					break;
				case 1511:
					H1511(num,percent);
					break;
				case 1512:
					H1512(num,percent);
					break;
				case 1513:
					H1513(num,percent);
					break;
				case 1521:
					H1521(num,percent);
					break;
				case 1522:
					H1522(num,percent);
					break;
				case 1523:
					H1523(num,percent);
					break;
				case 1531:
					H1531(num,percent);
					break;
				case 1532:
					H1532(num,percent);
					break;
				case 1533:
					H1533(num,percent);
					break;
				case 1611:
					H1611(num,percent);
					break;
				case 1612:
					H1612(num,percent);
					break;
				case 1613:
					H1613(num,percent);
					break;
				case 1621:
					H1621(num,percent);
					break;
				case 1622:
					H1622(num,percent);
					break;
				case 1623:
					H1623(num,percent);
					break;
				case 1631:
					H1631(num,percent);
					break;
				case 1632:
					H1632(num,percent);
					break;
				case 1633:
					H1633(num,percent);
					break;
				case 1711:
					H1711(num,percent);
					break;
				case 1712:
					H1712(num,percent);
					break;
				case 1713:
					H1713(num,percent);
					break;
				case 1721:
					H1721(num,percent);
					break;
				case 1722:
					H1722(num,percent);
					break;
				case 1723:
					H1723(num,percent);
					break;
				case 1731:
					H1731(num,percent);
					break;
				case 1732:
					H1732(num,percent);
					break;
				case 1733:
					H1733(num,percent);
					break;
				case 1811:
					H1811(num,percent);
					break;
				case 1812:
					H1812(num,percent);
					break;
				case 1813:
					H1813(num,percent);
					break;
				case 1821:
					H1821(num,percent);
					break;
				case 1822:
					H1822(num,percent);
					break;
				case 1823:
					H1823(num,percent);
					break;
				case 1831:
					H1831(num,percent);
					break;
				case 1832:
					H1832(num,percent);
					break;
				case 1833:
					H1833(num,percent);
					break;
				case 1911:
					H1911(num,percent);
					break;
				case 1912:
					H1912(num,percent);
					break;
				case 1913:
					H1913(num,percent);
					break;
				case 1921:
					H1921(num,percent);
					break;
				case 1922:
					H1922(num,percent);
					break;
				case 1923:
					H1923(num,percent);
					break;
				case 1931:
					H1931(num,percent);
					break;
				case 1932:
					H1932(num,percent);
					break;
				case 1933:
					H1933(num,percent);
					break;

				default:
					printf("There are not such alternative hypothesis! \n");
					exit(0);
					break;
			}
		}

		~AlternativeHypotheses()
		{
			if( D != NULL )
				delete [] D;
			else
				D = NULL;
		}

		Distribution *D;
};

#endif
