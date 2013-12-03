#ifndef EMAILCUSTOMER_H
#define EMAILCUSTOMER_H

#include "simlib.h" 
#include <stdio.h>
#include <iostream>


class EmailCustomer : public Process 
{ 
  
 public: 
  EmailCustomer(); //konstruktor
  ~EmailCustomer(); //destruktor


  double prichod;    // atribute of each customer 
  void Behavior();    // --- behavoir specification --- 


 private:


}; 


class GeneratorEmail : public Event
{
public:
	GeneratorEmail();
	~GeneratorEmail();

	EmailCustomer * muj;

	void Behavior();
};

#endif //EMAILCUSTOMER_H