#include "cpu.h"

Cpu::Cpu(int countCore, int countProccessors, Ram *ram, HardDisk *hardDisk, Histogram *myTable)
{

	numberPower = countCore * countProccessors;
	processorsPower.SetCapacity(numberPower);
	myHardDisk = hardDisk;
	myRam = ram;
	hist = myTable;
	maxCyclePerRound = 100000;
	frequency = 3000000000;
	cyclePerByte = 1000000;
	//maxCyclePerRound;
}
//-----------------------------------------------------------

Cpu::~Cpu()
{

}
//-----------------------------------------------------------

double Cpu::countTime(unsigned long fileSize)
{
	return ((fileSize * cyclePerByte) / frequency);
}
//-----------------------------------------------------------

double Cpu::cacheCountTime(unsigned long fileSize)
{
	//zde jeste dodelat, jak je rychla cache
	return ((fileSize * cyclePerByte) / (frequency - 100));
}

//-----------------------------------------------------------

double Cpu::countTimeWrite(unsigned long fileSize)
{

	return (myRam->accessTime + myHardDisk->timeWriteHardisk(fileSize));
}

//-----------------------------------------------------------

double Cpu::countTimeRead(unsigned long fileSize, int *isHDD)
{
	//v 80% je to nekde jinde, ve 20% je to v Cache
	if ((myRandValue(100, 1)) <= 20)
	{
		//velikost, pokud to neni nakesovane
		return cacheCountTime(fileSize);

	}
	else if ((myRandValue(100, 1)) <= 40)
	{
		//accessTime Cache zanedbavame
		return myRam->timeReadRam(fileSize);
	}
	else
	{
		*isHDD = 1;
		//bereme v uvahu vybaveni Ramky, vybavovaci dobu Cache zanedbavame
		return (myRam->accessTime + myHardDisk->timeReadHardisk(fileSize));

	}

}
//-----------------------------------------------------------

int Cpu::myRandValue(unsigned long myMod, int plus)
{
	return ((rand() % myMod) + plus);

}
//------------------------------------------------------------

void Cpu::emailCustomerRead(EmailCustomer *actualCust, unsigned long size)
{
	int isHDD, myTime;

	isHDD = 0;
	actualCust->Enter(processorsPower, 1);

	//kolik ma jeden email?
	myTime = countTimeRead(size, &isHDD);
	if (isHDD)
	{
		actualCust->Enter(myHardDisk->numberDisc, 1);
	}
	actualCust->Wait(myTime);

	if (isHDD)
	{
		actualCust->Leave(myHardDisk->numberDisc, 1);
	}
	actualCust->Leave(processorsPower, 1);

}
//------------------------------------------------------------

void Cpu::emailCustomerWrite(EmailCustomer *actualCust, unsigned long size)
{
	double myTime;

	actualCust->Enter(processorsPower, 1);

	//kolik ma jeden email?
	myTime = countTimeWrite(size);
	actualCust->Enter(myHardDisk->numberDisc, 1);
	actualCust->Wait(myTime);
	actualCust->Leave(myHardDisk->numberDisc, 1);
	actualCust->Leave(processorsPower, 1);

}
//------------------------------------------------------------

void Cpu::ftpCustomerRead(FtpCustomer *actualCust, unsigned long size)
{
	int isHDD, myTime;

	isHDD = 0;
	actualCust->Enter(processorsPower, 1);

	//kolik ma jeden email?
	myTime = countTimeRead(size, &isHDD);
	if (isHDD)
	{
		actualCust->Enter(myHardDisk->numberDisc, 1);
	}
	actualCust->Wait(myTime);

	if (isHDD)
	{
		actualCust->Leave(myHardDisk->numberDisc, 1);
	}
	actualCust->Leave(processorsPower, 1);

}
//------------------------------------------------------------

void Cpu::ftpCustomerWrite(FtpCustomer *actualCust, unsigned long size)
{
	double myTime;

	actualCust->Enter(processorsPower, 1);

	//prumerny soubor?
	myTime = countTimeWrite(size);
	actualCust->Enter(myHardDisk->numberDisc, 1);
	actualCust->Wait(myTime);
	actualCust->Leave(myHardDisk->numberDisc, 1);
	actualCust->Leave(processorsPower, 1);

}
//------------------------------------------------------------

void Cpu::streamCustomerRead(StreamCustomer *actualCust, unsigned long size)
{
	int isHDD, myTime;

	isHDD = 0;
	actualCust->Enter(processorsPower, 1);

	//kolik ma jeden email?
	myTime = countTimeRead(size, &isHDD);
	if (isHDD)
	{
		actualCust->Enter(myHardDisk->numberDisc, 1);
	}
	actualCust->Wait(myTime);

	if (isHDD)
	{
		actualCust->Leave(myHardDisk->numberDisc, 1);
	}
	actualCust->Leave(processorsPower, 1);

}
//------------------------------------------------------------

void Cpu::streamCustomerWrite(StreamCustomer *actualCust, unsigned long size)
{
	double myTime;

	actualCust->Enter(processorsPower, 1);

	//prumerny soubor?
	myTime = countTimeWrite(size);
	actualCust->Enter(myHardDisk->numberDisc, 1);
	actualCust->Wait(myTime);
	actualCust->Leave(myHardDisk->numberDisc, 1);
	actualCust->Leave(processorsPower, 1);

}

//------------------------------------------------------------

unsigned long Cpu::numberRound(unsigned long waitTime, double *lastRound)
{ 
	*lastRound = (double) (waitTime % maxCyclePerRound);
  return waitTime / maxCyclePerRound;
}