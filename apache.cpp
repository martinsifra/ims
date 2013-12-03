#include "apache.h"


Apache::Apache(int countProccess)
{

  maxCreateProccess = countProccess;
  proccess.SetCapacity(maxCreateProccess);

}

Apache::~Apache()
{
  

}

void Apache::createNewProccess()
{
  /*printf("Budu chtit vzit hlavni proces\n");
  if(mainProccessApache.Busy())
   {
  	printf("Je zabrany, budu cekat\n");
   }
  else
   {
   	printf("Beru si ho\n");
   }
    
   Seize(mainProccessApache);
   //provadim generovani noveho procesu
   Wait(50);
   Release(mainProccessApache); */
}