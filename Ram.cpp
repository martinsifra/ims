#include "ram.h"

Ram::Ram(
  unsigned long accessTimeRamPar,
	unsigned long frequencyRamPar,
	unsigned long speedOfReadRamPar,
	unsigned long cyclePerByteRamPar
)
{ 
	
	accessTime = accessTimeRamPar;
	frequency = frequencyRamPar;
	speedOfRead = speedOfReadRamPar;
	cyclePerByte = cyclePerByteRamPar;
	
}

Ram::~Ram()
{
	
	
}


double Ram::timeReadRam(unsigned long fileSize)
{
  return (((fileSize * cyclePerByte) / frequency) + accessTime);	
	
}