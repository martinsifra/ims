#include "apache.h"

Apache::Apache(int countProccess)
{

	maxCreateProccess = countProccess;
	proccess.SetCapacity(maxCreateProccess);

}
//-----------------------------------------------------------

Apache::~Apache()
{


}
//----------------------------------------------------------

void Apache::createNewEmailProccess(EmailCustomer *actualCust)
{
	printf("Jsem EMAIL zakaznik!!\n");

	double lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->countTime(actualCust->myCpu->myPar->timeCreateNewProcess), &lastRound);
	for (unsigned long i = round; i >= 0; i--)
	{
		actualCust->Enter(actualCust->myCpu->processorsPower, 1);
		actualCust->Seize(mainProccessApache);
		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			actualCust->Wait((double) actualCust->myCpu->maxCyclePerRound);
		}
		else
		{
			actualCust->Wait(lastRound);
		}
		actualCust->Release(mainProccessApache);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);
	}
	//(*actualCust->myCpu->hist)(Time- (actualCust->prichod));

}
//---------------------------------------------------------

void Apache::createNewFtpProccess(FtpCustomer *actualCust)
{
	printf("Jsem FTP zakaznik!!!\n");

	double lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->countTime(actualCust->myCpu->myPar->timeCreateNewProcess), &lastRound);
	for (unsigned long i = round; i >= 0; i--)
	{
		actualCust->Enter(actualCust->myCpu->processorsPower, 1);
		actualCust->Seize(mainProccessApache);
		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			actualCust->Wait((double) actualCust->myCpu->maxCyclePerRound);
		}
		else
		{
			actualCust->Wait(lastRound);
		}
		actualCust->Release(mainProccessApache);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);
	}
	//(*actualCust->myCpu->hist)(Time- (actualCust->prichod));
}

//---------------------------------------------------------------

void Apache::createNewStreamProccess(StreamCustomer *actualCust)
{
	printf("Jsem FTP zakaznik!!!\n");

	double lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->countTime(actualCust->myCpu->myPar->timeCreateNewProcess), &lastRound);
	for (unsigned long i = round; i >= 0; i--)
	{
		actualCust->Enter(actualCust->myCpu->processorsPower, 1);
		actualCust->Seize(mainProccessApache);
		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			actualCust->Wait((double) actualCust->myCpu->maxCyclePerRound);
		}
		else
		{
			actualCust->Wait(lastRound);
		}
		actualCust->Release(mainProccessApache);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);
	}
	//(*actualCust->myCpu->hist)(Time- (actualCust->prichod));
}