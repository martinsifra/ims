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
	
	std::ofstream  Trafic;
	Trafic.open ("Trafic.txt");
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
					par.throughputRam
					);
	//pameti a ostatni budou ulozeny v procesoru
	Cpu myCPU( &myRam, &myHardDisk, &hist, &par);
//pocet hlavnich procesu podle poctu servru
	Apache myApache( par.processorCpu);
  
	//printf("%lu /  %lu", par.startTime, par.endTime);
	Init(par.startTime, par.endTime);

	(new GeneratorEmail(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	(new GeneratorFtp(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	(new GeneratorStream(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	Run();
	
	printf("Celkove emailu: %lu\n", myApache.Email);
	printf("Celkove ftp: %lu\n", myApache.Ftp);
	printf("Celkove stream: %lu\n", myApache.Stream);
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
	
	myCPU.network.Output();
	myCPU.outPackeQ.Output();
	
	Trafic << ((myCPU.outTrafic) * 1500 ) << "\n";
	
	Trafic.close();
	
	//hist.Output();
	
	return 0;
}