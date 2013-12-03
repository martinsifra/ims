#include "apache.h"

Apache::Apache(int countProccess)
{

	maxCreateProccess = countProccess;
	proccess.SetCapacity(maxCreateProccess);

}

Apache::~Apache()
{


}

void Apache::createNewProccess(EmailCustomer *actualCust)
{
	printf("Budu chtit vzit hlavni proces\n");
  
	//zabereme si hlavni proccess
	actualCust->Seize(mainProccessApache);
	actualCust->Enter(actualCust->myCpu->processorsPower, 1);
	//provadim generovani noveho procesu
	actualCust->Wait(50);
	
	actualCust->Leave(actualCust->myCpu->processorsPower, 1);
	actualCust->Release(mainProccessApache);
	double tmpPrichod = actualCust->prichod;
	(*actualCust->myCpu->hist)(Time-tmpPrichod);
	return;
}