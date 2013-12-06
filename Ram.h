#ifndef RAM_H
#define RAM_H

#include "simlib.h" 
//#include "global.h"

class Ram { 
public:
	Ram(
					unsigned long accessTimeRamPar,
					unsigned long frequencyRamPar,
					unsigned long speedOfReadRamPar,
					unsigned long cyclePerByteRamPar
					); //konstruktor
	~Ram(); //destruktor

	unsigned long accessTime;
	unsigned long frequency;
	unsigned long cyclePerByte;

	double timeReadRam(unsigned long sizeFile);


private:
	unsigned long speedOfRead;


};

#endif //RAM_H