#include "streamCustomer.h"


//konstruktor

StreamCustomer::StreamCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;


}

//destruktor

StreamCustomer::~StreamCustomer()
{


}

void StreamCustomer::Behavior()
{

	prichod = Time;
	//vytvarime novy proces
	myApache->createNewStreamProccess(this);
	
	//


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
	Activate(Time + Exponential(ROZLOZENIGENEROVANI)); // zde se aktivuje


}