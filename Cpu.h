#ifndef CPU_H
#define CPU_H

#include "simlib.h" 
#include "hardDisk.h"
#include "ram.h"
#include "emailCustomer.h"
#include <stdlib.h>
#include "parseParam.h"
#include "Request.h"

class EmailCustomer;
class FtpCustomer;
class StreamCustomer;
class ParseParam;
class Request;

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
	Queue waitingProcess;
	unsigned long counterEPID;
	unsigned long counterFPID;
	unsigned long counterSPID;



	/**
	 * @brief Funkce pro vypocet casu pri cteni z Cache, ktery bude procesor cekat
	 * @param fileSize Velikost souboru v B
	 * @return vrati cas procesoru, ktery t
	 */
	double countTime(unsigned long fileSize);
	//double cacheCountTime(unsigned long fileSize);
	double countTimeRead(unsigned long fileSize, int *isHDD);
	double countTimeWrite(unsigned long fileSize);
	int myRandValue(unsigned long myMod, int plus);
	unsigned long countrujE();
	unsigned long countrujF();
	unsigned long countrujS();


	void requestRead(Request *actualCust, unsigned long size);
	void requestWrite(Request *actualCust, unsigned long size);

	unsigned long numberRound(unsigned long time, double *lastRound);
	unsigned long maxCyclePerRound;

private:
	unsigned long numberPower;
	unsigned long frequency;
	unsigned long cyclePerByte;



};

#endif //CPU_H