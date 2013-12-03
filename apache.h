#ifndef APACHE_H
#define APACHE_H

#include "simlib.h"
//#include "global.h" 
#include <stdio.h>

class Apache 
{ 
  
 public: 
   Apache(int countProccess); //konstruktor
  ~Apache(); //destruktor
   
   void createNewProccess();

   Store proccess;
   Facility mainProccessApache; //hlavni proces, ktery bezi furt
   
    
	 

 private:
 	int maxCreateProccess;
  

}; 

#endif //APACHE_H