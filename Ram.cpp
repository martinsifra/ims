#include "ram.h"

Ram::Ram(
  unsigned long accessTimeRamPar,
	unsigned long throughputPar
)
{ 
	
	accessTime = accessTimeRamPar;
	throughput = throughputPar;

	
}

Ram::~Ram()
{
	
	
}


double Ram::timeReadRam(unsigned long fileSize)
{
  return (fileSize / throughput) + accessTime;	
	
}