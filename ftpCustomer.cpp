#include "ftpCustomer.h"


//konstruktor

FtpCustomer::FtpCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;




}

//destruktor
//--------------------------------------------
FtpCustomer::~FtpCustomer()
{


}
//--------------------------------------------

void FtpCustomer::parseHeaderReq()
{
	printf("Zpracuji pozadavek - hlavicku\n");
	double lastRound;
	unsigned long round = myCpu->numberRound(myCpu->countTime(headerSize), &lastRound);
	for (unsigned long i = round; i >= 0; i--)
	{
		Enter(myCpu->processorsPower, 1);
		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			Wait((double)myCpu->maxCyclePerRound);
		}
		else
		{
			Wait(lastRound);
		}
		Leave(myCpu->processorsPower, 1);
	}
}
//--------------------------------------------

//------------------------------------
void FtpCustomer::findReqFile()
{
	//nez se doklikame k pozadovanemu souboru
	unsigned long sizeDemandFile = 500;
	
	
	//nez se doklikame k pozadovanemu souboru
	myCpu->ftpCustomerRead(this, sizeDemandFile);
	
	//kolik souboru budeme cist
	
	//kolik souboru budeme zapisovat
	
}

//--------------------------------------------
void FtpCustomer::Behavior()
{
	prichod = Time;
	
	//vytvarime novy proces
	myApache->createNewFtpProccess(this);
 
	//zpracovavam pozadavek
	parseHeaderReq();
	
	findReqFile();
	
	
	

}


//-------------------------------------------
//--------------------------------------------
GeneratorFtp::GeneratorFtp(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;

}

GeneratorFtp::~GeneratorFtp()
{



}

void GeneratorFtp::Behavior()
{ // --- behavior specification --- 

	(new FtpCustomer(myApache, myCpu))->Activate(); // novy email customer
	Activate(Time + Exponential(ROZLOZENIGENEROVANI)); // zde se aktivuje


}