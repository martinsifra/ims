#include "hardDisk.h"


HardDisk::HardDisk()
{
	accessTime = 100;
	//capacity = ;
	speedOfRead = 4000;
	speedOfWrite = 2000;
	numberDisc.SetCapacity(20);
}

HardDisk::~HardDisk()
{
	
}


double HardDisk::timeReadHardisk(unsigned long sizeFile)
{
  return ((sizeFile/speedOfRead) + accessTime);	
	
}

double HardDisk::timeWriteHardisk(unsigned long sizeFile)
{
  return ((sizeFile/speedOfWrite) + accessTime);	
	
}