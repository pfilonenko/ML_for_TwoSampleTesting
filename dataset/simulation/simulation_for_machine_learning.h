#ifndef simulation_for_machine_learning_H
#define simulation_for_machine_learning_H

#include"HelpFucntions.h"

// Object of the data simulation for training of the proposed ML-method
class simulation_for_machine_learning{
	private:
		// p-value computation using the Test and Test Statistic (Sn)
		double pvalue(double Sn, HomogeneityTest* Test)
		{
			auto f = Test->F( Sn );
			double pv = 0;
			if( Test->TestType().c_str() == "right" )
				pv = 1.0 - f;
			else
				if( Test->TestType().c_str() == "left" )
					pv = f;
				else    // "double"
					pv = 2.0*min( f, 1-f );
			return pv;
		}

		// Process of simulation
		void Simulation(int iter, vector<HomogeneityTest*> &D, int rank, mt19937boost Gw)
		{
			// ñôîðìèðîâàëè íàçâàíèå ôàéëà äëÿ ñîõðàíåíèÿ
			char file_to_save[512];
			sprintf(file_to_save,".//to_machine_learning_2024//to_machine_learning[rank=%d].csv", rank);

			// åñëè ýòî ñàìàÿ ïåðâàÿ èòåðàöèÿ, òî ñîõðàíèëè øàïêó ôàéëà
			if( iter == 0 )
			{
				FILE *ou = fopen(file_to_save,"w");
				fprintf(ou, "num;H0/H1;model;n1;n2;perc;real_perc1;real_perc2;");
				for(int i=0; i<D.size(); i++)
				{
					char title_of_test[512];
					D[i]->TitleTest(title_of_test);
					fprintf(ou, "Sn [%s];p-value [%s];", title_of_test, title_of_test);
				}
				fprintf(ou, "\n");
				fclose(ou);
			}

			// Getting list of the Alternative Hypotheses (H01 - H27)
			vector<int> H;
			int l = 1;
			for(int i=100; i<940; i+=100)			// Groups of Alternative Hypotheses (I, II, III, IV, V, VI, VII, VIII, IX)
			{
				for(int j=10; j<40; j+=10)			// Alternative Hypotheses in the Group (e.g., H01, H02, H03 into the I and so on)
					//for(int l=1; l<4; l++)		// various families of distribution of censoring time F^C(t)
						H.push_back( 1000+i+j+l );
			}

			// Sample sizes
			vector<int> sample_sizes;
			sample_sizes.push_back( 20 );	// n1 = n2 = 20
			sample_sizes.push_back( 30 );	// n1 = n2 = 30
			sample_sizes.push_back( 50 );	// n1 = n2 = 50
			sample_sizes.push_back( 75 );	// n1 = n2 = 75
			sample_sizes.push_back( 100 );	// n1 = n2 = 100
			sample_sizes.push_back( 150 );	// n1 = n2 = 150
			sample_sizes.push_back( 200 );	// n1 = n2 = 200
			sample_sizes.push_back( 300 );	// n1 = n2 = 300
			sample_sizes.push_back( 500 );	// n1 = n2 = 500
			sample_sizes.push_back( 1000 );	// n1 = n2 = 1000

			// Simulation (Getting H, Simulation samples, Computation of the test statistics & Save to file)
			for(int i = 0; i<H.size(); i++)
			{
				int Hyp = H[i];
		
				if(rank == 0)
					printf("\tH = %d\n",Hyp);

				for(int per = 0; per<51; per+=10)
				{
					// ---- Getting Hi ----
					AlternativeHypotheses H0_1(Hyp,1,0), H0_2(Hyp,2,0);
					AlternativeHypotheses H1_1(Hyp,1,per), H1_2(Hyp,2,per);

					for(int jj=0; jj<sample_sizes.size(); jj++)
					{
						int n = sample_sizes[jj];

						// ---- Simulation samples ----
						//competing hypothesis Í0
						Sample A0(*H0_1.D,n,Gw);
						Sample B0(*H0_1.D,n,Gw);
						if( per > 0 )
						{
							A0.CensoredTypeThird(*H1_1.D,Gw);
							B0.CensoredTypeThird(*H1_1.D,Gw);
						}

						//competing hypothesis Í1
						Sample A1(*H0_1.D,n,Gw);
						Sample B1(*H0_2.D,n,Gw);
						if( per > 0 )
						{
							A1.CensoredTypeThird(*H1_1.D,Gw);
							B1.CensoredTypeThird(*H1_2.D,Gw);
						}

						// ---- Computation of the test statistics & Save to file ----
						//Sn and p-value computation under Í0
						FILE *ou = fopen(file_to_save, "a");
						auto perc1 = A0.RealCensoredPercent();
						auto perc2 = B0.RealCensoredPercent();
						fprintf(ou,"%d;", iter);
						fprintf(ou,"H0;");
						fprintf(ou,"%d;", Hyp);
						fprintf(ou,"%d;%d;", n,n);
						fprintf(ou,"%d;%lf;%lf", per, perc1, perc2);
						for(int j=0; j<D.size(); j++)
						{
							auto Sn_H0 = D[j]->CalculateStatistic(A0, B0);
							auto pv_H0 = 0.0;	// skip computation (it prepares in ML-framework)
							fprintf(ou, ";%lf;0", Sn_H0);
						}
						fprintf(ou, "\n");

						//Sn and p-value computation under Í1
						perc1 = A1.RealCensoredPercent();
						perc2 = B1.RealCensoredPercent();
						fprintf(ou,"%d;", iter);
						fprintf(ou,"H1;");
						fprintf(ou,"%d;", Hyp);
						fprintf(ou,"%d;%d;", n,n);
						fprintf(ou,"%d;%lf;%lf", per, perc1, perc2);
						for(int j=0; j<D.size(); j++)
						{
							auto Sn_H1 = D[j]->CalculateStatistic(A1, B1);
							auto pv_H1 = 0.0;  // skip computation (it prepares in ML-framework)
							fprintf(ou, ";%lf;0", Sn_H1);
						}
						fprintf(ou, "\n");
						fclose( ou );
					}
				}
			}
		}

	public:
		// Constructor of the class
		simulation_for_machine_learning(vector<HomogeneityTest*> &D)
		{
			int N = 37650;	// number of the Monte-Carlo replications
			#pragma omp parallel for
			for(int k=0; k<N; k++)
			{
				int rank = omp_get_thread_num();
				auto gen = GwMT19937[rank];
		
				if(rank == 0)
					printf("\r%d", k);

				Simulation(k, D, rank, gen);
			}
		}
};

#endif
