#include "streamCustomer.h"


//konstruktor

StreamCustomer::StreamCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;
 
	headerSize = myCpu->myPar->sizeHeaderHttp;

}

//destruktor

StreamCustomer::~StreamCustomer()
{


}

void StreamCustomer::watchVideo()
{
	int numberVideo = myCpu->myRandValue(5, 1);
	//zde bude velikost 1 souboru, ktery se bude stahovat

	for (int i = 1; i <= numberVideo; i++)
	{
		parseHeaderReq();
		myCpu->streamCustomerRead(this, myCpu->myPar->averageVideoStream);
	}

}

void StreamCustomer::parseHeaderReq()
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

void StreamCustomer::Behavior()
{

	prichod = Time;
	//vytvarime novy proces
	myApache->createNewStreamProccess(this);

	//hlavicku zpracujeme
	parseHeaderReq();

	watchVideo();

}

//-------------------------------------------

GeneratorStream::GeneratorStream(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;

}

GeneratorStream::~GeneratorStream()
{



}

void GeneratorStream::Behavior()
{ // --- behavior specification --- 

	(new StreamCustomer(myApache, myCpu))->Activate(); // novy email customer
	Activate(Time + Exponential(myCpu->myPar->generateStream)); // zde se aktivuje


}