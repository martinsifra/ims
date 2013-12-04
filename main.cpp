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

#define POCETJADER 10
#define POCETPROCESORU 10
#define MAXPROCESUAPACHE 10


int main()
{
  Histogram hist("Table",0,25,20);
  //to budeme resit nejakou konstantou od - do
	SetOutput("model.txt");
  
   
  //zde budeme nastavovat velikost HDD, pristupovou dobu, atd. HDD
	HardDisk myHardDisk;
	//zde budeme nastavovat parametry RAM
	Ram myRam;
	//pameti a ostatni budou ulozeny v procesoru
  Cpu myCPU(POCETJADER, POCETPROCESORU, &myRam ,&myHardDisk, &hist);
  Apache myApache(MAXPROCESUAPACHE);
  
	Init(0,1000); 

  (new GeneratorEmail(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	(new GeneratorFtp(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
	(new GeneratorStream(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
   Run(); 
   myApache.mainProccessApache.Output();
	 myApache.proccess.Output();
	 
	 myCPU.processorsPower.Output();
	 hist.Output();
 return 0;
}