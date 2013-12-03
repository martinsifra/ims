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
	printf("Budu chtit vzit hlavni proces\n");
  if(myApache->mainProccessApache.Busy())
   {
  	printf("Je zabrany, budu cekat\n");
   }
  else
   {
   	printf("Beru si ho\n");
   }
    
   Seize(myApache->mainProccessApache);
   //provadim generovani noveho procesu
   Wait(50);
   Release(myApache->mainProccessApache);
	 
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