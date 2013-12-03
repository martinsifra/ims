#ifndef STREAMCUSTOMER_H
#define STREAMCUSTOMER_H

#include "simlib.h" 


class StreamCustomer : public Process
{
  
 public: 
  StreamCustomer(); //konstruktor
  ~StreamCustomer(); //destruktor


  double prichod;    // atribute of each customer 
  void behavior();    // --- behavoir specification --- 


 private:

}; 

#endif //STREAMCUSTOMER_H