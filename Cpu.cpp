#include "cpu.h"

Cpu::Cpu(int countCore, int countProccessors, Ram *ram, HardDisk *hardDisk, Histogram *myTable)
{

	numberPower = countCore * countProccessors;
	processorsPower.SetCapacity(numberPower);
	myHardDisk = hardDisk;
	myRam = ram;	
	hist = myTable;
}

Cpu::~Cpu()
{

}

void Cpu::setPowerUnit(EmailCustomer *actualCustom)
{
	//zebereme si jednu vypocetni jednotku
	actualCustom->Enter(processorsPower,1);
}