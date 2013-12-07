#include "hardDisk.h"

HardDisk::HardDisk(
				unsigned long accessTimePar,
				unsigned long speedOfReadPar,
				unsigned long speedOfWritePar,
				unsigned long countHddpar
				)
{
	accessTime = accessTimePar;
	speedOfRead = speedOfReadPar;
	speedOfWrite = speedOfWritePar;
	numberDisc.SetCapacity(countHddpar);
	
	numberDisc.SetQueue(waitingForHDD);
}

HardDisk::~HardDisk()
{

}

double HardDisk::timeReadHardisk(unsigned long sizeFile)
{
	return ((sizeFile / speedOfRead) + accessTime);

}

double HardDisk::timeWriteHardisk(unsigned long sizeFile)
{
	return ((sizeFile / speedOfWrite) + accessTime);

}