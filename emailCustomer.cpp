#include "emailCustomer.h"

EmailCustomer::EmailCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;

	//zde se priradi nahodna velikost hlavicky
	headerSize = myCpu->myPar->sizeHeaderHttp;
	PID = cpu->countrujE();

}

//------------------------------------------

EmailCustomer::~EmailCustomer()
{


}

//---------------------------------------------

void EmailCustomer::Behavior()
{
	prichod = Time;

//	printf("%lu: Novy Email - Req\n", PID);

	//vytvarime novy proces
	myApache->createNewEmailProccess(this);

}


//--------------------------------------------
//--------------------------------------------

GeneratorEmail::GeneratorEmail(Apache *apache, Cpu * cpu)
{
	myApache = apache;
	myCpu = cpu;

}
//--------------------------------------------

GeneratorEmail::~GeneratorEmail()
{



}

//--------------------------------------------

void GeneratorEmail::Behavior()
{ // --- behavior specification --- 

	(new EmailCustomer(myApache, myCpu))->Activate(); // novy email customer
	
	Activate(Time + Exponential(myCpu->myPar->generateEmail)); // zde se aktivuje


}