#include "simlib.h" 
//#include "global.h"
#include "emailCustomer.h"
#include "ftpCustomer.h"
#include "streamCustomer.h"
#include "cpu.h"
#include "apache.h"
#include "hardDisk.h"
#include "ram.h"
#include <stdio.h>
#include "parseParam.h"

int main()
{
	Histogram hist("Table", 0, 25, 20);
	//to budeme resit nejakou konstantou od - do
	SetOutput("model.txt");

	ParseParam par("params");

	if (par.err != "")
	{
		fprintf(stderr, "%s\n", par.err.c_str());
		return 2;
	}

	//zde budeme nastavovat velikost HDD, pristupovou dobu, atd. HDD
	HardDisk myHardDisk(
					par.accessTimeHdd,
					par.speedOfReadHdd,
					par.speedOfWriteHdd,
					par.countHdd
					);


	//zde budeme nastavovat parametry RAM
	Ram myRam(
					par.accessTimeRam,
					par.frequencyRam,
					par.speedOfReadRam,
					par.cyclePerByteRam
					);
	//pameti a ostatni budou ulozeny v procesoru
	Cpu myCPU(par.coreCpu, par.processorCpu, &myRam, &myHardDisk, &hist, &par);
//pocet hlavnich procesu podle poctu servru
	Apache myApache( par.processorCpu);

	Init(par.startTime, par.endTime);

	(new GeneratorEmail(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	(new GeneratorFtp(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	(new GeneratorStream(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	Run();
	
	//hlavni proces apache
	myApache.mainProccessApache.Output();
	//cekani ve fronte na apache
	myApache.incomingReq.Output();
  
	
	//cekani na procesor
	myCPU.processorsPower.Output();
	//cekani ve fronte
	myCPU.waitingProcess.Output();

	//cekani na HDD
	myHardDisk.numberDisc.Output();
	//cekani ve fronte na HDD
	myHardDisk.waitingForHDD.Output();
	
	//hist.Output();
	
	return 0;
}