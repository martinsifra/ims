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

void Apache::createNewEmailProccess(EmailCustomer *actualECust)
{
	printf("Jsem EMAIL zakaznik!!\n");

	//zabereme si hlavni proccess
	actualECust->Seize(mainProccessApache);
	printf("Zabral jsem si apache - hlavni \n");
	actualECust->Enter(actualECust->myCpu->processorsPower, 1);
	//provadim generovani noveho procesu
	actualECust->Wait(10);

	actualECust->Leave(actualECust->myCpu->processorsPower, 1);
	actualECust->Release(mainProccessApache);
	//(*actualECust->myCpu->hist)(Time- (actualECust->prichod));
}
//---------------------------------------------------------

void Apache::createNewFtpProccess(FtpCustomer *actualFCust)
{
	printf("Jsem FTP zakaznik!!!\n");

	//zabereme si hlavni proccess
	actualFCust->Seize(mainProccessApache);
	actualFCust->Enter(actualFCust->myCpu->processorsPower, 1);
	//provadim generovani noveho procesu
	actualFCust->Wait(50);

	actualFCust->Leave(actualFCust->myCpu->processorsPower, 1);
	actualFCust->Release(mainProccessApache);
	(*actualFCust->myCpu->hist)(Time - (actualFCust->prichod));
}

//---------------------------------------------------------------

void Apache::createNewStreamProccess(StreamCustomer *actualSCust)
{
	printf("Jsem stream zakaznik!!\n");

	//zabereme si hlavni proccess
	actualSCust->Seize(mainProccessApache);
	actualSCust->Enter(actualSCust->myCpu->processorsPower, 1);
	//provadim generovani noveho procesu
	actualSCust->Wait(50);

	actualSCust->Leave(actualSCust->myCpu->processorsPower, 1);
	actualSCust->Release(mainProccessApache);
	(*actualSCust->myCpu->hist)(Time - (actualSCust->prichod));
}