#ifndef HARDDISK_H
#define HARDDISK_H

#include "simlib.h" 
//#include "global.h"

class HardDisk {
public:
	HardDisk(
					unsigned long accessTimePar,
					unsigned long speedOfReadPar,
					unsigned long speedOfWritePar,
					unsigned long countHddpar
					); //konstruktor
	~HardDisk(); //destruktor

	Store numberDisc;
	Queue waitingForHDD;
	double timeReadHardisk(unsigned long sizeFile);
	double timeWriteHardisk(unsigned long sizeFile);
  
	
private:
	unsigned long accessTime;
	unsigned long capacity;
	unsigned long speedOfRead;
	unsigned long speedOfWrite;



};

#endif //HARDDISK_H