#include "simlib.h" 
//#include "global.h"
#include "emailCustomer.h"
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
  
  //to budeme resit nejakou konstantou od - do
  Init(0,1000); 
   
  //zde budeme nastavovat velikost HDD, pristupovou dobu, atd. HDD
	HardDisk myHardDisk;
	//zde budeme nastavovat parametry RAM
	Ram myRam;
	//pameti a ostatni budou ulozeny v procesoru
  Cpu myCPU(POCETJADER, POCETPROCESORU, &myRam ,&myHardDisk);
  Apache myApache(MAXPROCESUAPACHE);


  (new GeneratorEmail(&myApache, &myCPU))->Activate(); // vygeneruje zakazniky a zaroven aktivuje
   Run(); 
   
 return 0;
}