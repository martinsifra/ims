#include "emailCustomer.h"


//konstruktor
EmailCustomer::EmailCustomer(Apache *apache, Cpu *cpu)
{
  myApache = apache;
  myCpu = cpu;

} 
//destruktor
EmailCustomer::~EmailCustomer()
{


} 

void EmailCustomer::Behavior()
{ 
	prichod = Time;
	//vytvarime novy proces
	myApache->createNewEmailProccess(this);
	
	//pokud je vytvoreny novy proces, alokujeme si vypocetni jednotku
	myCpu->setPowerUnit(this);
	
	//zde budeme resit, co kdo bude chtit delat atd
  
}




GeneratorEmail::GeneratorEmail(Apache *apache, Cpu *cpu)
{
  myApache = apache;
  myCpu = cpu;

}

GeneratorEmail::~GeneratorEmail()
{


	
}


void GeneratorEmail::Behavior()
{ // --- behavior specification --- 
  
  (new EmailCustomer(myApache, myCpu))->Activate(); // novy email customer
  Activate(Time+Exponential(ROZLOZENIGENEROVANI)); // zde se aktivuje

  
  }