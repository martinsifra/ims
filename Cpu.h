#ifndef CPU_H
#define CPU_H

#include "simlib.h" 
#include "hardDisk.h"
#include "ram.h"
#include "emailCustomer.h"
#include <stdlib.h>
#include "parseParam.h"

class EmailCustomer;
class FtpCustomer;
class StreamCustomer;
class ParseParam;

class Cpu { 
public:
	Cpu(int countCore, int countProccessors, Ram *ram, HardDisk *hardDisk, Histogram *myTable,
					ParseParam *par); //konstruktor
	~Cpu(); //destruktor

	Store processorsPower;
	Ram *myRam;
	HardDisk *myHardDisk;
	ParseParam * myPar;
	//void parseHeaderReq(EmailCustomer *actualECust);
	Histogram *hist;
	double countTime(unsigned long fileSize);
	double cacheCountTime(unsigned long fileSize);
	double countTimeRead(unsigned long fileSize, int *isHDD);
	double countTimeWrite(unsigned long fileSize);
	int myRandValue(unsigned long myMod, int plus);
	

	void emailCustomerRead(EmailCustomer *actualCust, unsigned long size);
	void emailCustomerWrite(EmailCustomer *actualCust, unsigned long size);
	void ftpCustomerRead(FtpCustomer *actualCust, unsigned long size);
	void ftpCustomerWrite(FtpCustomer *actualCust, unsigned long size);
	void streamCustomerRead(StreamCustomer *actualCust, unsigned long size);
	void streamCustomerWrite(StreamCustomer *actualCust, unsigned long size);

	unsigned long numberRound(unsigned long waitTime, double *lastRound);
	unsigned long maxCyclePerRound;

private:
	unsigned long numberPower;
	unsigned long frequency;
	unsigned long cyclePerByte;



};

#endif //CPU_H