#include"simulation_for_machine_learning.h"

//Selected two-sample tests
vector<HomogeneityTest*> AllTests()
{
	vector<HomogeneityTest*> D;
	
	// ---- Classical Two-Sample tests for Uncensored Case ----
	//D.push_back( new HT_AndersonDarlingPetitt );
	//D.push_back( new HT_KolmogorovSmirnovTest );
	//D.push_back( new HT_LehmannRosenblatt );
	
	// ---- Two-Sample tests for Right-Censored Case ----
	D.push_back( new HT_Peto );
	D.push_back( new HT_Gehan );
	D.push_back( new HT_Logrank );
	
	D.push_back( new HT_BagdonaviciusNikulinGeneralizedCox );
	D.push_back( new HT_BagdonaviciusNikulinMultiple );
	D.push_back( new HT_BagdonaviciusNikulinSingle );

	D.push_back( new HT_QTest );			//based on the Kaplan-Meier estimator
	D.push_back( new HT_MAX );				//Maximum Value test
	D.push_back( new HT_SynthesisTest );	//MIN3 test
	
	D.push_back( new HT_WeightedLogrank("logrank") );
	D.push_back( new HT_WeightedLogrank("Tarone–Ware") );
	D.push_back( new HT_WeightedLogrank("Breslow") );
	D.push_back( new HT_WeightedLogrank("Peto–Prentice") );
	D.push_back( new HT_WeightedLogrank("Prentice") );
	
	D.push_back( new HT_WeightedKaplanMeyer );
		
	return D;
}

// Example of two-sample testing using this code
void EXAMPLE_1(vector<HomogeneityTest*> &D)
{
	// load the samples
	Sample T1(".//samples//1Chemotherapy.txt");
	Sample T2(".//samples//2Radiotherapy.txt");

	// two-sample testing through selected tests
	for(int j=0; j<D.size(); j++)
	{
		char test_name[512];
		D[j]->TitleTest(test_name);
		

		double Sn = D[j]->CalculateStatistic(T1, T2);
		double pvalue = D[j]->p_value(T1, T2, 1000);

		printf("%s\n", &test_name);
		printf("\t Sn: %lf\n", Sn);
		printf("\t pv: %lf\n", pvalue);
		printf("--------------------------------");
	}
}

// Example of the dataset simulation for the proposed ML-method
void EXAMPLE_2(vector<HomogeneityTest*> &D)
{
	// Run dataset (train or test sample) simulation (results in ".//to_machine_learning_2024//")
	simulation_for_machine_learning sm(D);
}

// init point
int main()
{
	// Set the number of threads
	int k = omp_get_max_threads() - 1;
	//int k = 1;
	omp_set_num_threads( k );

	// Select two-sample tests
	auto D = AllTests();
	
	// Example of two-sample testing using this code
	EXAMPLE_1(D);

	// Example of the dataset simulation for the proposed ML-method
	EXAMPLE_2(D);

	// Freeing memory
	ClearMemory(D);
	
	printf("The mission is completed.\n");
	return 0;
}
