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

	actualCust->Seize(mainProccessApache);
	//provadim generovani noveho procesu
	actualCust->Wait(50);
	actualCust->Release(mainProccessApache);
	return;
}