#ifndef CPU_H
#define CPU_H

#include "simlib.h" 
#include "hardDisk.h"
#include "ram.h"



class Cpu 
{ 
  
 public: 
  Cpu(int countCore, int countProccessors, Ram *ram, HardDisk *hardDisk); //konstruktor
  ~Cpu(); //destruktor

 Store processorsPower;
 Ram * myRam;
 HardDisk *myHardDisk;


 private:
    unsigned long numberPower;

}; 

#endif //CPU_H