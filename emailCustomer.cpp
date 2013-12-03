#include "emailCustomer.h"


//konstruktor
EmailCustomer::EmailCustomer()
{


} 

//destruktor
EmailCustomer::~EmailCustomer()
{


} 

void EmailCustomer::Behavior()
{ 
  //prichod = Time;  // incoming time 
  //Seize(Box);       // start of service 
  Wait(100);        // time of service 
  //Release(Box);     // end of service 
  //Table(Time-prichod); // waiting and service time 
  
  printf("Jsem zde\n");
  
  
}




GeneratorEmail::GeneratorEmail()
{



}

GeneratorEmail::~GeneratorEmail()
{


	
}


void GeneratorEmail::Behavior()
{ // --- behavior specification --- 
  
  (new EmailCustomer)->Activate(); // novy email customer
  Activate(Time+Exponential(10)); // zde se aktivuje

  
  }