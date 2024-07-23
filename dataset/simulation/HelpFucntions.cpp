#include"HelpFucntions.h"

// Freeing memory
void ClearMemory(vector<HomogeneityTest*> &D)
{
	for(int i=0; i<D.size(); i++)
		delete D[i];
}
