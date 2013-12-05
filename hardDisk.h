#ifndef HARDDISK_H
#define HARDDISK_H

#include "simlib.h" 
//#include "global.h"

class HardDisk { 
public:
	HardDisk(); //konstruktor
	~HardDisk(); //destruktor
	
	Store numberDisc;
	double timeReadHardisk(unsigned long sizeFile);
	double timeWriteHardisk(unsigned long sizeFile);

private:
	unsigned long accessTime;
	unsigned long capacity;
	unsigned long speedOfRead;
	unsigned long speedOfWrite;



};

#endif //HARDDISK_H