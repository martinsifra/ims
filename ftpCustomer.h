#ifndef FTPCUSTOMER_H
#define FTPCUSTOMER_H

#include "simlib.h" 


class FtpCustomer : public Process 
{ 
  
 public: 
  FtpCustomer(); //konstruktor
  ~FtpCustomer(); //destruktor


  double prichod;    // atribute of each customer 
  void behavior();    // --- behavoir specification --- 


 private:

}; 

#endif //FTPCUSTOMER_H