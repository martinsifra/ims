#include "cpu.h"

Cpu::Cpu(int countCore, int countProccessors, Ram *ram, HardDisk *hardDisk)
{

	numberPower = countCore * countProccessors;
	processorsPower.SetCapacity(numberPower);
	myHardDisk = hardDisk;
	myRam = ram;	
}

Cpu::~Cpu()
{

}

void Cpu::setPowerUnit(EmailCustomer *actualCustom)
{
	//zebereme si jednu vypocetni jednotku
	actualCustom->Enter(processorsPower,1);
}