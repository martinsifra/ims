#ifndef HARDDISK_H
#define HARDDISK_H

#include "simlib.h" 
//#include "global.h"


class HardDisk 
{ 
  
 public: 
  HardDisk(); //konstruktor
  ~HardDisk(); //destruktor


 private:
	 int accessTime;
	 int capacity;
	 
  

}; 

#endif //HARDDISK_H