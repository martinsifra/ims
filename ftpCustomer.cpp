#include "ftpCustomer.h"


//konstruktor

FtpCustomer::FtpCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;




}

//destruktor

FtpCustomer::~FtpCustomer()
{


}

void FtpCustomer::Behavior()
{
	prichod = Time;
	//vytvarime novy proces
	myApache->createNewFtpProccess(this);


}


//-------------------------------------------

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