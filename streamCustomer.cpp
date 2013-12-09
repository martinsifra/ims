#include "streamCustomer.h"


//konstruktor

StreamCustomer::StreamCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;

	headerSize = myCpu->myPar->sizeHeaderHttp;

	PID = cpu->countrujS();
}

//destruktor

StreamCustomer::~StreamCustomer()
{


}

//---------------------------------------------------

void StreamCustomer::Behavior()
{

	prichod = Time;
	(*myCpu->histPozadavky)(Time);
	(*myCpu->histPozadavkyS)(Time);

//	printf("%lu: Novy STREAM - Req\n", PID);
	//vytvarime novy proces
	myApache->createNewStreamProccess(this);

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