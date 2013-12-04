#ifndef FTPCUSTOMER_H
#define FTPCUSTOMER_H

#include "simlib.h" 
#include <stdio.h>
#include <iostream>
//#include "global.h"
#include "cpu.h"
#include "apache.h"

#define ROZLOZENIGENEROVANI 10


class Apache;
class Cpu;

class FtpCustomer : public Process 
{ 
  
 public: 
  FtpCustomer(Apache *apache, Cpu *cpu); //konstruktor
  ~FtpCustomer(); //destruktor


  double prichod;    // atribute of each customer 
  void Behavior();    // --- behavoir specification --- 

  Cpu *myCpu;
  Apache *myApache;
	
 private:
	 

}; 

class GeneratorFtp : public Event
{
public:
	GeneratorFtp(Apache *apache, Cpu *cpu);
	~GeneratorFtp();


private:
	void Behavior();
	Cpu *myCpu;
  Apache *myApache;
};


#endif //FTPCUSTOMER_H