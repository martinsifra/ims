#include "cpu.h"


Cpu::Cpu(int countCore, int countProccessors, Ram *ram, HardDisk *hardDisk)
{
  
  numberPower = countCore * countProccessors ;
  processorsPower.SetCapacity(numberPower);
	myHardDisk = hardDisk;
	myRam = ram;

}

Cpu::~Cpu()
{


	
}