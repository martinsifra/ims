#include "simlib.h" 
#include "emailCustomer.h"
#include "streamCustomer.h"
#include "ftpCustomer.h"
#include "hardDisk.h"
#include "Ram.h"
#include "Cpu.h"
#include <stdio.h>




int main()
{
  
  //to budeme resit nejakou konstantou od - do
  Init(0,1000); 

  (new GeneratorEmail)->Activate(); // vzgeneruje zakazniky
   Run(); 
   
 return 0;
}