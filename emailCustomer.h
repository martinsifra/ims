#ifndef EMAILCUSTOMER_H
#define EMAILCUSTOMER_H

#include "simlib.h" 
#include <stdio.h>
#include <iostream>
#include "cpu.h"
#include "apache.h"

class Apache;
class Cpu;
class ParseParam;

class EmailCustomer : public Process {
public:
	EmailCustomer(Apache *apache, Cpu *cpu); //konstruktor
	~EmailCustomer(); //destruktor


	double prichod; // atribute of each customer 
	void Behavior(); // --- behavoir specification --- 
	Cpu *myCpu;
	Apache *myApache;
	//v B
	unsigned long headerSize;
	unsigned long PID;

private:


};

class GeneratorEmail : public Event {
public:
	GeneratorEmail(Apache *apache, Cpu *cpu);
	~GeneratorEmail();


private:
	void Behavior();
	Cpu *myCpu;
	Apache *myApache;
};

#endif //EMAILCUSTOMER_H