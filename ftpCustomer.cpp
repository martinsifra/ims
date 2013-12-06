#include "ftpCustomer.h"


//konstruktor

FtpCustomer::FtpCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;
	
	headerSize = myCpu->myPar->sizeHeaderHttp;




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
			Wait((double) myCpu->maxCyclePerRound);
		}
		else
		{
			Wait(lastRound);
		}
		Leave(myCpu->processorsPower, 1);
	}
}
//--------------------------------------------

void FtpCustomer::uploadFile()
{
	if (myCpu->myRandValue(100, 1) < 90)
	{
		int numberFile = myCpu->myRandValue(5, 1);
		//zde bude velikost 1 souboru, ktery se bude stahovat

		for (int i = 1; i <= numberFile; i++)
		{
			parseHeaderReq();
			myCpu->ftpCustomerWrite(this, myCpu->myPar->averageFileFtp);
		}
	}
}
//--------------------------------------------

void FtpCustomer::downloadFile()
{
	if (myCpu->myRandValue(100, 1) < 60)
	{
		int numberFile = myCpu->myRandValue(5, 1);

		
		for (int i = 1; i <= numberFile; i++)
		{
			parseHeaderReq();
			myCpu->ftpCustomerRead(this, myCpu->myPar->averageFileFtp);
		}
	}
}
//------------------------------------

void FtpCustomer::findReqFile()
{
	//nez se doklikame k pozadovanemu souboru

	parseHeaderReq();
	//nez se doklikame k pozadovanemu souboru
	myCpu->ftpCustomerRead(this, myCpu->myPar->sizeDemandFileFtp);

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

	uploadFile();
	
	downloadFile();



}


//-------------------------------------------
//--------------------------------------------

GeneratorFtp::GeneratorFtp(Apache *apache, Cpu * cpu)
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
	Activate(Time + Exponential(myCpu->myPar->generateFtp)); // zde se aktivuje


}