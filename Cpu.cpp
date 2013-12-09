#include "cpu.h"

Cpu::Cpu(Ram *ram, HardDisk *hardDisk, ParseParam *par)
{

	numberPower = par->coreCpu * par->processorCpu * par->threadsCpu;
	processorsPower.SetCapacity(numberPower);
	processorsPower.SetQueue(&waitingProcess);

	sizePacket = 1500;

	unsigned long maxPacket = (unsigned long) par->capacityNetwork / 1500;
	network.SetCapacity(maxPacket);
	network.SetQueue(&outPackeQ);

	myHardDisk = hardDisk;
	myRam = ram;
	myPar = par;
	maxCyclePerRound = par->maxCyclePerRoundCpu;
	frequency = par->frequencyCpu;
	cyclePerByte = par->cyclePerByteCpu;
	counterEPID = counterFPID = counterSPID = 0;

	bytePercycle = maxCyclePerRound / cyclePerByte;

	desNetwork = network.Capacity() / 10;

	outTrafic = 0;

	srand(time(NULL));


	Email.open("Email.txt");
	Ftp.open("Ftp.txt");
	Stream.open("Stream.txt");
	VytizeniHDD.open("VytizeniHDD.txt");



}
//-----------------------------------------------------------

Cpu::~Cpu()
{
	Email.close();
	Ftp.close();
	Stream.close();
	VytizeniHDD.close();

}
//-----------------------------------------------------------

unsigned long Cpu::countCycle(unsigned long fileSize)
{
	return ((fileSize * cyclePerByte));
}

//-----------------------------------------------------------

double Cpu::countTimeWrite(unsigned long fileSize)
{
	//vraci velikost souboru/rychlost zapisu + accessTime HDD
	return (myHardDisk->timeWriteHardisk(fileSize));
}

//-----------------------------------------------------------

double Cpu::countTimeRead(unsigned long fileSize, int *typeMemory)
{
	//v 80% je to nekde jinde, ve 20% je to v Cache
	int value = myRandValue(100, 1);

	if (value <= 10 && fileSize < 512000)
	{
		//velikost, pokud to neni nakesovane
		*typeMemory = 1;
		return countTime(countCycle(fileSize));

	}
	else if (value > 10 && value <= 25 && fileSize < 16000000)
	{
		*typeMemory = 2;
		//vraci velikostsouboru/propustnost
		return myRam->timeReadRam(fileSize);
	}
	else
	{
		*typeMemory = 3;
		//bereme v uvahu vybaveni Ramky, vybavovaci dobu Cache zanedbavame
		//vraci velikostsouboru/rychlostcteni + accesTime HDD + accesTIme ram
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
	int typeMemory, amIwait;
	unsigned long lastRound;
	typeMemory = 0;
	int countPacket;
	unsigned long round = numberRound(countCycle(size), &lastRound);

	double timeMemory = countTimeRead(size, &typeMemory);

	//jake je aktualni vytizeni HDD
	(*actualCust->myCpu->histVytizeniHDD)(myHardDisk->numberDisc.Free());


	if (typeMemory == 3)
	{
		//najmu si procesor, aby vystavil pozadavek na pamet
		amIwait = 0;
		while (1)
		{
			//musime najmout procesor
			if (canHireCpu(actualCust, &amIwait) == 1)
				break;
		}

		actualCust->Enter(processorsPower, 1);
		//cekame, nez procesor zpracuje pozadavky na cteni
		//actualCust->Wait(1);

		//uvolnime procesor a povolime prvniho ve fronte
		leaveCpuStartNext(actualCust);

		//zabirame HDD
		amIwait = 0;
		while (1)
		{
			//musime najmout HDD
			if (canHireHDD(actualCust, &amIwait) == 1)
				break;
		} 
		
		actualCust->Enter(myHardDisk->numberDisc, 1);
			VytizeniHDD << Time << " " << (myHardDisk->numberDisc.Used()) << "\n";
		//cteme z HDD 
		actualCust->Wait(timeMemory);

		//opoustim HDD a davam poustim dalsi, co cekaji na HDD
		leaveHddStartNext(actualCust);
	}
	else //cteme z Ram nebo Cache
	{
		//najmu si procesor, aby vystavil pozadavek na pamet
		amIwait = 0;
		while (1)
		{
			//musime najmout procesor
			if (canHireCpu(actualCust, &amIwait) == 1)
				break;
		}
		
		actualCust->Enter(processorsPower, 1);
		//cekame, nez procesor zpracuje pozadavky na cteni
		//actualCust->Wait(2); 


		if (typeMemory == 1)
			//cteme rychlosti procesoru
			actualCust->Wait(timeMemory);
		else
			//jinak z ramek
			actualCust->Wait(myRam->timeReadRam(size));

		//uvolnime procesor a povolime prvniho ve fronte
		leaveCpuStartNext(actualCust);

	} // konec else

	//zpracuji data z pameti do paketu
	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;
		while (1)
		{
			//musime najmout procesor
			if (canHireCpu(actualCust, &amIwait) == 1)
				break;
		}
		
		actualCust->Enter(processorsPower, 1);

		if (i != 0)
		{
			actualCust->Wait(countTime(maxCyclePerRound));
		}
		else
		{
			actualCust->Wait(countTime(lastRound));
		}
		leaveCpuStartNext(actualCust);

	}

	//mame nactene data, rozbijeme je do paketu
	countPacket = (size / sizePacket);
	while (countPacket > 0)
	{
		int freePackets = network.Free();
		//zabirame pakety
		if (freePackets > 3 * desNetwork)
		{
			freePackets = 3 * desNetwork;
		}
		amIwait = 0;
		while (1)
		{
			if (canHirePacket(actualCust, &amIwait, freePackets) == 1)
				break;
		}

		actualCust->Enter(network, freePackets);

		outTrafic += freePackets;

		countPacket -= freePackets;
		//odesilame vterinu
		//actualCust->Wait(1);

		actualCust->Leave(network, freePackets);

		if (!outPackeQ.Empty())
		{
			(outPackeQ.GetFirst())->Activate();
			//outPackeQ.Insert(actualCust);
		}
	}
	//******************************************************************************


}
//------------------------------------------------------------

void Cpu::requestWrite(Request *actualCust, unsigned long size)
{
	int amIwait;

	amIwait = 0;
	while (1)
	{
		//musime najmout procesor
		if (canHireCpu(actualCust, &amIwait) == 1)
			break;
	}

	actualCust->Enter(processorsPower, 1);
	//cekame, nez procesor zpracuje pozadavky na cteni
	actualCust->Wait(1);


	//uvolnime procesor a povolime prvniho ve fronte
	leaveCpuStartNext(actualCust);

	//zabirame HDD
	amIwait = 0;
	while (1)
	{
		//musime najmout HDD
		if (canHireHDD(actualCust, &amIwait) == 1)
			break;
	}
	actualCust->Enter(myHardDisk->numberDisc, 1);

	//zapisujeme na HDD 
	actualCust->Wait(myHardDisk->timeWriteHardisk(size));

	//opoustim HDD a davam poustim dalsi, co cekaji na HDD
	leaveHddStartNext(actualCust);

}
//------------------------------------------------------------

//------------------------------------------------------------

unsigned long Cpu::numberRound(unsigned long cycle, unsigned long *lastRound)
{
	//time = (filesize * cyclePerRound)
	*lastRound = (cycle % maxCyclePerRound);

	return cycle / maxCyclePerRound;
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

void Cpu::leaveCpuStartNext(Request * actualCust)
{

	actualCust->Leave(processorsPower, 1);

	if (!actualCust->myApache->incomingReq.Empty() && !actualCust->myApache->mainProccessApache.Full())
	{
		(actualCust->myApache->incomingReq.GetFirst())->Activate();
	}

	if (waitingProcess.Length() > 0)
	{
		(waitingProcess.GetFirst())->Activate();
		//waitingProcess.Insert(actualCust);
	}

}

void Cpu::leaveHddStartNext(Request * actualCust)
{
	actualCust->Leave(myHardDisk->numberDisc, 1);

	if (myHardDisk->waitingForHDD.Length() > 0)
	{
		(myHardDisk->waitingForHDD.GetFirst())->Activate();
		//myHardDisk->waitingForHDD.Insert(actualCust);
	}

}
//--------------------------------------------------------

int Cpu::canHireHDD(Request *actualCust, int *amIwait)
{
	int can = 0;
	if (myHardDisk->numberDisc.Full())
	{
		(*amIwait)++;
		myHardDisk->waitingForHDD.Insert(actualCust);
		actualCust->Passivate();
	}
	else
	{
		//pokud nekdo ceka a ja jsem necekal = dam mu prednost
		if (!myHardDisk->waitingForHDD.Empty() && (*amIwait) == 0)
		{
			(*amIwait)++;
			(myHardDisk->waitingForHDD.GetFirst())->Activate();
			myHardDisk->waitingForHDD.Insert(actualCust);
			actualCust->Passivate();
		}
		else
		{
			can = 1;
		}
	}
	return can;
}

///-----------------------------------------------------

int Cpu::canHireCpu(Request *actualCust, int *amIwait)
{
	int can = 0;
	if (processorsPower.Full())
	{
		(*amIwait)++;
		waitingProcess.Insert(actualCust);
		actualCust->Passivate();
	}
	else
	{
		//pokud nekdo ceka a ja jsem necekal = dam mu prednost
		if (!waitingProcess.Empty() && (*amIwait) == 0)
		{
			(*amIwait)++;
			(waitingProcess.GetFirst())->Activate();
			waitingProcess.Insert(actualCust);
			actualCust->Passivate();
		}
		else
		{
			can = 1;
		}
	}
	return can;
}

int Cpu::canHirePacket(Request *actualCust, int *amIwait, unsigned long countPacket)
{
	int can = 0;
	if (network.Free() < countPacket)
	{
		(*amIwait)++;

		outPackeQ.Insert(actualCust);
		actualCust->Passivate();
	}
	else
	{
		//pokud nekdo ceka a ja jsem necekal = dam mu prednost
		if (!outPackeQ.Empty() && amIwait == 0)
		{
			(*amIwait)++;
			(outPackeQ.GetFirst())->Activate();
			outPackeQ.Insert(actualCust);
			actualCust->Passivate();
		}
		else
			can = 1;
	}
	return can;
}

double Cpu::countTime(unsigned long cycle)
{
	return cycle / frequency;
}