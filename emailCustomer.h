#ifndef EMAILCUSTOMER_H
#define EMAILCUSTOMER_H

#include "simlib.h" 
#include <stdio.h>
#include <iostream>
//#include "global.h"
#include "cpu.h"
#include "apache.h"

#define ROZLOZENIGENEROVANI 10

class Apache;
class Cpu;

class EmailCustomer : public Process 
{ 
  
 public: 
  EmailCustomer(Apache *apache, Cpu *cpu); //konstruktor
  ~EmailCustomer(); //destruktor


  double prichod;    // atribute of each customer 
  void Behavior();    // --- behavoir specification --- 


 private:
   Cpu *myCpu;
   Apache *myApache;

}; 


class GeneratorEmail : public Event
{
public:
	GeneratorEmail(Apache *apache, Cpu *cpu);
	~GeneratorEmail();


private:
	void Behavior();
	Cpu *myCpu;
    Apache *myApache;
};

#endif //EMAILCUSTOMER_H