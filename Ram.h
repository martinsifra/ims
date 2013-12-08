#ifndef RAM_H
#define RAM_H

#include "simlib.h" 
//#include "global.h"

class Ram { 
public:
	Ram(
					unsigned long accessTimeRamPar,
					unsigned long throughputPar
					); //konstruktor
	~Ram(); //destruktor

	unsigned long accessTime;
	unsigned long throughput;

	double timeReadRam(unsigned long sizeFile);


private:
	unsigned long speedOfRead;


};

#endif //RAM_H