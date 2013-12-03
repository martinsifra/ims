#ifndef APACHE_H
#define APACHE_H

#include "simlib.h"
#include "emailCustomer.h"
//#include "global.h" 
#include <stdio.h>

class EmailCustomer;

class Apache 
{ 
  
 public: 
   Apache(int countProccess); //konstruktor
  ~Apache(); //destruktor
   
   void createNewProccess(EmailCustomer *actualCust);

   Store proccess;
   Facility mainProccessApache; //hlavni proces, ktery bezi furt


 private:
 	int maxCreateProccess;
  

}; 

#endif //APACHE_H