#ifndef CPU_H
#define CPU_H

#include "simlib.h" 
#include "hardDisk.h"
#include "ram.h"
#include "emailCustomer.h"
#include <stdlib.h>
#include "parseParam.h"
#include "Request.h"
#include <fstream>

class EmailCustomer;
class FtpCustomer;
class StreamCustomer;
class ParseParam;
class Request;

class Cpu {
public:
	Cpu(Ram *ram, HardDisk *hardDisk, Histogram *myTable,
					ParseParam *par); //konstruktor
	~Cpu(); //destruktor

	Store processorsPower;
	Queue waitingProcess;
	
	Ram *myRam;
	HardDisk *myHardDisk;
	ParseParam * myPar;
	//void parseHeaderReq(EmailCustomer *actualECust);
	Histogram *hist;
	
	Store network;
	Queue outPackeQ;
	
	unsigned long counterEPID;
	unsigned long counterFPID;
	unsigned long counterSPID;



	/**
	 * @brief Funkce pro vypocet casu pri cteni z Cache, ktery bude procesor cekat
	 * @param fileSize Velikost souboru v B
	 * @return vrati cas procesoru, ktery t
	 */
	unsigned long countCycle(unsigned long fileSize);
	//double cacheCountTime(unsigned long fileSize);
	double countTimeRead(unsigned long fileSize, int *isHDD);
	double countTimeWrite(unsigned long fileSize);
	int myRandValue(unsigned long myMod, int plus);
	unsigned long countrujE();
	unsigned long countrujF();
	unsigned long countrujS();
 
	double countTime(unsigned long cycle);

	void requestRead(Request *actualCust, unsigned long size);
	void requestWrite(Request *actualCust, unsigned long size);
	
	void leaveCpuStartNext(Request *actualCust);
	void leaveHddStartNext(Request *actualCust);
	
	int canHireCpu(Request *actualCust, int *amIwait);
	int canHirePacket(Request *actualCust, int *amIwait, unsigned long countPacket);
	int canHireHDD(Request *actualCust, int *amIwait);

	unsigned long numberRound(unsigned long cycle, unsigned long *lastRound);
	unsigned long maxCyclePerRound;
	unsigned long bytePercycle;
	
	unsigned long outTrafic;
	
	int desNetwork;
	
	std::ofstream  Email;
	std::ofstream  Stream;
	std::ofstream  Ftp;


private:
	unsigned long numberPower;
	unsigned long frequency;
	unsigned long cyclePerByte;
	
	unsigned long sizePacket;



};

#endif //CPU_H