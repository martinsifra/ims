#include "ftpCustomer.h"


//konstruktor

FtpCustomer::FtpCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;

	headerSize = myCpu->myPar->sizeHeaderHttp;

	PID = cpu->countrujF();


}

//destruktor
//--------------------------------------------

FtpCustomer::~FtpCustomer()
{


}
//--------------------------------------------


//--------------------------------------------

void FtpCustomer::Behavior()
{
	prichod = Time;

	//vytvarime novy proces
//	printf("%lu: Nove FTP - Req\n", PID);
	myApache->createNewFtpProccess(this);

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