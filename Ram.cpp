#include "ram.h"

Ram::Ram()
{ 
	frequency = 15000;
	speedOfRead = 8000;
	cyclePerByte = 5000;
	
}

Ram::~Ram()
{
	
	
}

double Ram::timeReadRam(unsigned long fileSize)
{
  return (((fileSize * cyclePerByte) / frequency) + accessTime);	
	
}