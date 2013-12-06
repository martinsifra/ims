#ifndef STREAMCUSTOMER_H
#define STREAMCUSTOMER_H

#include "simlib.h" 
#include <stdio.h>
#include <iostream>
//#include "global.h"
#include "cpu.h"
#include "apache.h"

#define ROZLOZENIGENEROVANI 10

class Apache;
class Cpu;

class StreamCustomer : public Process {
public:
	StreamCustomer(Apache *apache, Cpu *cpu); //konstruktor
	~StreamCustomer(); //destruktor


	double prichod; // atribute of each customer 
	void Behavior(); // --- behavoir specification --- 
	Cpu *myCpu;
	Apache *myApache;
	unsigned long headerSize;
	void watchVideo();
	void parseHeaderReq();
	
private:

};

class GeneratorStream : public Event {
public:
	GeneratorStream(Apache *apache, Cpu *cpu);
	~GeneratorStream();


private:
	void Behavior();
	Cpu *myCpu;
	Apache *myApache;
};



#endif //STREAMCUSTOMER_H