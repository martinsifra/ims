#include "cpu.h"

Cpu::Cpu(int countCore, int countProccessors, Ram *ram, HardDisk *hardDisk, Histogram *myTable,
				ParseParam *par)
{

	numberPower = countCore * countProccessors;
	processorsPower.SetCapacity(numberPower);
	myHardDisk = hardDisk;
	myRam = ram;
	hist = myTable;
	myPar = par;
	maxCyclePerRound = par->maxCyclePerRoundCpu;
	frequency = par->frequencyCpu;
	cyclePerByte = par->cyclePerByteCpu;
	processorsPower.SetQueue(&waitingProcess);
	counterEPID = counterFPID = counterSPID = 0;


}
//-----------------------------------------------------------

Cpu::~Cpu()
{

}
//-----------------------------------------------------------

double Cpu::countTime(unsigned long fileSize)
{
	return ((fileSize * cyclePerByte) / frequency);
}

//-----------------------------------------------------------

double Cpu::countTimeWrite(unsigned long fileSize)
{

	return (myHardDisk->timeWriteHardisk(fileSize));
}

//-----------------------------------------------------------

double Cpu::countTimeRead(unsigned long fileSize, int *isHDD)
{
	//v 80% je to nekde jinde, ve 20% je to v Cache
	int value = myRandValue(100, 1);

	if (value <= 10)
	{
		//velikost, pokud to neni nakesovane
		return countTime(fileSize);

	}
	else if (value > 10 && <= 25)
	{
		//accessTime Cache zanedbavame
		return myRam->timeReadRam(fileSize);
	}
	else
	{
		*isHDD = 1;
		//bereme v uvahu vybaveni Ramky, vybavovaci dobu Cache zanedbavame

		return (myRam->accessTime + myHardDisk->timeReadHardisk(fileSize));

	}

}
//-----------------------------------------------------------

int Cpu::myRandValue(unsigned long myMod, int plus)
{

	return ((rand() % myMod) + plus);

}
//------------------------------------------------------------

void Cpu::requestRead(Request *actualCust, unsigned long size)
{
	int isHDD, amIwait;
	double lastRound;
	isHDD = 0;
	printf("%lu: %s - READ DATA  \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());

	unsigned long round = numberRound((countTimeRead(size, &isHDD)), &lastRound);

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;
		while (1)
		{
			if (isHDD)
			{
				printf("%lu: %s - READ DATA - z HDD \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
				//je volny HDD
				if (myHardDisk->numberDisc.Full() || processorsPower.Full())
				{
					//zvedneme pocitadlo
					amIwait++;

					printf("%lu: %s - READ DATA - z HDD - jdu do fronty \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
					//neni, cekame na dalsi
					myHardDisk->waitingForHDD.Insert(actualCust);
					actualCust->Passivate();
				}
				else
				{
					printf("%lu: %s - READ DATA - z HDD - mam volno \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
					//pokud je volny HDD, chceme procesor
					if (!myHardDisk->waitingForHDD.Empty() && amIwait == 0)
					{
						printf("%lu: %s - READ DATA - z HDD - davam prednost cekajicimu \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());


						(myHardDisk->waitingForHDD.GetFirst())->Activate();
						myHardDisk->waitingForHDD.Insert(actualCust);
						actualCust->Passivate();
					}
					else
						break;
				}
			}
			else //bez HDD
			{
				printf("%lu: %s - READ DATA - CACHE|RAM \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
				//pokud je to bez HDD, chceme procesor
				if (processorsPower.Full())
				{
					printf("%lu: %s - READ DATA - CACHE|RAM - neni procesor \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
					amIwait++;

					waitingProcess.Insert(actualCust);
					actualCust->Passivate();
				}
				else
				{
					//pokud nekdo ceka a ja jsem necekal = dam mu prednost
					if (!waitingProcess.Empty() && amIwait == 0)
					{
						printf("%lu: %s - READ DATA - CACHE|RAM - davam prednost cekajicimu \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());

						amIwait++;
						(waitingProcess.GetFirst())->Activate();
						waitingProcess.Insert(actualCust);
						actualCust->Passivate();
					}
					else
						break;
				}
			}

		}


		printf("%lu: %s - READ DATA - zabiram procesor \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
		actualCust->Enter(processorsPower, 1);

		if (isHDD)
		{
			printf("%lu: %s - READ DATA - zabiram HDD \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
			actualCust->Enter(myHardDisk->numberDisc, 1);
		}

		if (i != 0)
		{
			printf("%lu: %s - READ DATA - cekam round \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
			actualCust->Wait((double) maxCyclePerRound);
		}
		else
		{
			printf("%lu: %s - READ DATA - cekam zbytek \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
			actualCust->Wait(lastRound);
		}

		if (isHDD)
		{
			printf("%lu: %s - READ DATA - opoustim HDD \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
			actualCust->Leave(myHardDisk->numberDisc, 1);
		}

		printf("%lu: %s - READ DATA - opoustim procesor \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
		actualCust->Leave(processorsPower, 1);

		if (isHDD)
		{
			if (myHardDisk->waitingForHDD.Length() > 0)
			{
				printf("%lu: %s - READ DATA - HDD - pokud nekdo ceka na neho, povolim ho \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
				(myHardDisk->waitingForHDD.GetFirst())->Activate();
			}
		}

		if (waitingProcess.Length() > 0)
		{

			printf("%lu: %s - READ DATA - PROCESOR - pokud nekdo ceka na neho, povolim ho \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
			(waitingProcess.GetFirst())->Activate();
		}


	}

}
//------------------------------------------------------------

void Cpu::requestWrite(Request *actualCust, unsigned long size)
{
	int amIwait;
	double lastRound;

	printf("%lu: %s - WRITE DATA \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
	unsigned long round = numberRound((countTimeWrite(size)), &lastRound);

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;
		while (1)
		{
			//je volny HDD
			if (myHardDisk->numberDisc.Full() || processorsPower.Full())
			{
				//zvedneme pocitadlo
				amIwait++;

				printf("%lu: %s - WRITE DATA -  HDD - jdu do fronty  \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
				//neni, cekame na dalsi
				myHardDisk->waitingForHDD.Insert(actualCust);
				actualCust->Passivate();
			}
			else
			{
				printf("%lu: %s - WRITE DATA -  HDD - mam volno \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
				//pokud je volny HDD, chceme procesor
				if (!myHardDisk->waitingForHDD.Empty() && amIwait == 0)
				{
					printf("%lu: %s - WRITE DATA - HDD - davam prednost cekajicimu \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());


					(myHardDisk->waitingForHDD.GetFirst())->Activate();
					myHardDisk->waitingForHDD.Insert(actualCust);
					actualCust->Passivate();
				}
				else
					break;
			}

		}



		printf("%lu: %s - WRITE DATA -  HDD - zabiram procesor \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
		actualCust->Enter(processorsPower, 1);

		printf("%lu: %s - WRITE DATA - zabiram HDD \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
		actualCust->Enter(myHardDisk->numberDisc, 1);

		if (i != 0)
		{
			printf("%lu: %s - WRITE DATA - cekam kolo \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
			actualCust->Wait((double) maxCyclePerRound);
		}
		else
		{
			printf("%lu: %s - WRITE DATA - cekam zbytek \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
			actualCust->Wait(lastRound);
		}

		printf("%lu: %s - WRITE DATA - opoustim procesor \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
		actualCust->Leave(processorsPower, 1);

		printf("%lu: %s - WRITE DATA - opoustim HDD \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
		actualCust->Leave(myHardDisk->numberDisc, 1);

		if (i != 0)
		{
			printf("%lu: Email - HDD zapis - poustim ostatni  \n", actualCust->PID);
			if (waitingProcess.Length() > 0)
			{
				printf("%lu: %s - WRITE DATA - aktivuji cekajiciho na procesor \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
				(waitingProcess.GetFirst())->Activate();
			}

			if (myHardDisk->waitingForHDD.Length() > 0)
			{

				printf("%lu: %s - WRITE DATA - aktivuji cekajiciho na HDD \n", actualCust->PID, (actualCust->typReq[actualCust->type]).c_str());
				(myHardDisk->waitingForHDD.GetFirst())->Activate();
			}
		}
	}
}
//------------------------------------------------------------

//------------------------------------------------------------

unsigned long Cpu::numberRound(unsigned long time, double *lastRound)
{
	*lastRound = (double) (time % maxCyclePerRound);

	return time / maxCyclePerRound;
}

unsigned long Cpu::countrujE()
{

	return counterEPID++;
}

unsigned long Cpu::countrujF()
{

	return counterFPID++;
}

unsigned long Cpu::countrujS()
{
	return counterSPID++;
}