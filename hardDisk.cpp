#include "hardDisk.h"

HardDisk::HardDisk(
				unsigned long accessTimePar,
				unsigned long capacityPar,
				unsigned long speedOfReadPar,
				unsigned long speedOfWritePar,
				unsigned long countHddpar
				)
{
	accessTime = accessTimePar;
	capacity = capacityPar;
	speedOfRead = speedOfReadPar;
	speedOfWrite = speedOfWritePar;
	numberDisc.SetCapacity(countHddpar);
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