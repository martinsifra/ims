#ifndef PARSEPARAM_H
#define	PARSEPARAM_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

class ParseParam {
public:
	ParseParam(std::string fileName);
	~ParseParam();

	//INITTIME
	unsigned long startTime;
	unsigned long endTime;
	
	//CPU
	unsigned long processorCpu;
	unsigned long coreCpu;
	unsigned long threadsCpu;
	unsigned long frequencyCpu;
	unsigned long cyclePerByteCpu;
	unsigned long maxCyclePerRoundCpu;

	//RAM
	unsigned long accessTimeRam;
	unsigned long throughputRam;

	//HDD
	unsigned long accessTimeHdd;
	unsigned long countHdd;
	unsigned long speedOfReadHdd;
	unsigned long speedOfWriteHdd;

	//HTTP
	unsigned long sizeHeaderHttp;

	//EMAIL
	unsigned long generateEmail;
	unsigned long listEmailSizeEmail;
	unsigned long oneEmailSizeEmail;
	unsigned long attachFilesSizeEmail;

	//FTP
	unsigned long generateFtp;
	unsigned long sizeDemandFileFtp;
	unsigned long averageFileFtp;

	//STREAM
	unsigned long generateStream;
	unsigned long averageVideoStream;

	//NETWORK
  unsigned long capacityNetwork;

	//APACHE
	//doba procesoru ztravena pri generovani noveho procesu v ms
	unsigned long timeCreateNewProcess;

	//ERR
	std::string err;
	
	unsigned long period;
  
	void parseFile();

private:
	std::ifstream myFile;
	
	unsigned long splitConvert(std::string readLine);

};

#endif	/* PARSEPARAM_H */

