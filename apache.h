#ifndef APACHE_H
#define APACHE_H

#include "simlib.h"
#include "emailCustomer.h"
#include "ftpCustomer.h"
#include "streamCustomer.h"
//#include "global.h" 
#include <stdio.h>

class EmailCustomer;
class FtpCustomer;
class StreamCustomer;

class Apache 
{ 
  
 public: 
   Apache(int countProccess); //konstruktor
  ~Apache(); //destruktor
   
	//simulace vytvareni procesu, ktery bude obsluhovat jednotlive zakazniky
   void createNewEmailProccess(EmailCustomer *actualECust);
	 void createNewFtpProccess(FtpCustomer *actualFCust);
	 void createNewStreamProccess(StreamCustomer *actualSCust);

   Store proccess;
   Facility mainProccessApache; //hlavni proces, ktery bezi furt


 private:
 	int maxCreateProccess;
  

}; 

#endif //APACHE_H