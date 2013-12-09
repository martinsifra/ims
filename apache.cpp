#include "apache.h"

Apache::Apache(int countMainProcces)
{
	//nastavime frontu pro prijimane pozadavky
	mainProccessApache.SetQueue(&incomingReq);
	mainProccessApache.SetCapacity(countMainProcces);
	Email = 0;
	Stream = 0;
	Ftp = 0;

	EmailP = FtpP = StreamP = 1;
}
//-----------------------------------------------------------

Apache::~Apache()
{


}
//----------------------------------------------------------

void Apache::createNewEmailProccess(EmailCustomer *actualCust)
{

	Email++;

	unsigned long lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->myPar->timeCreateNewProcess, &lastRound);
	printf("%lu: EMAIL - Apache pocet kol procesoru: %lu\n", actualCust->PID, round);

	int amIwait;

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;

		while (1)
		{
			if (actualCust->myCpu->processorsPower.Full() || mainProccessApache.Full())
			{
				amIwait++;
				if (actualCust->myCpu->processorsPower.Full())
					printf("%lu: EMAIL - Apache - jdu do fronty kvuli procesorum, i = %d \n", actualCust->PID, i);
				else
					printf("%lu: EMAIL - Apache - jdu do fronty kvuli apache, i = %d \n", actualCust->PID, i);
				incomingReq.Insert(actualCust);
				actualCust->Passivate();
			}
			else
			{
				printf("%lu: EMAIL - Apache - mam volno, i = %d \n", actualCust->PID, i);
				if (!incomingReq.Empty() && amIwait == 0)
				{
					amIwait++;
					printf("%lu: EMAIL - Apache - nekdo cekal, uvolnim ho, i = %d \n", actualCust->PID, i);
					(incomingReq.GetFirst())->Activate();
					incomingReq.Insert(actualCust);
					actualCust->Passivate();
				}
				else
					break;
			}
		}

		actualCust->Enter(actualCust->myCpu->processorsPower, 1);
		actualCust->Enter(mainProccessApache, 1);

		//pokud je zpracovavana doba vetsi nez maxCykluPerRound
		if (i != 0)
		{
			printf("%lu: EMAIL - Apache - cekam Round, i = %d \n", actualCust->PID, i);
			actualCust->Wait(actualCust->myCpu->countTime(actualCust->myCpu->maxCyclePerRound));
		}
		else
		{
			printf("%lu: EMAIL - Apache - cekam posledni, i = %d \n", actualCust->PID, i);
			actualCust->Wait(actualCust->myCpu->countTime(lastRound));
		}

		//ma byt Time v zavorce?
		(new Request(actualCust->myCpu, actualCust->myApache, 1, actualCust->PID))->Activate(Time);

		printf("%lu: EMAIL - Apache - uvolnuji hlavni proces, procesor, i = %d \n", actualCust->PID, i);
		//odebereme procesor, hlavni proces apachu
		actualCust->Leave(mainProccessApache, 1);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);

		if (!incomingReq.Empty())
		{
			printf("%lu: EMAIL - Apache - uvolnuji prvni proces ve fronte, i = %d \n", actualCust->PID, i);
			(incomingReq.GetFirst())->Activate();
		}


	}
	(*actualCust->myCpu->hist)(Time - (actualCust->prichod));

}
//---------------------------------------------------------

void Apache::createNewFtpProccess(FtpCustomer *actualCust)
{

	Ftp++;


	unsigned long lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->myPar->timeCreateNewProcess, &lastRound);
	printf("%lu: FTP - Apache pocet kol procesoru: %lu\n", actualCust->PID, round);

	int amIwait;

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;
		while (1)
		{
			if (actualCust->myCpu->processorsPower.Full() || mainProccessApache.Full())
			{
				amIwait++;
				printf("%lu: FTP - Apache - jdu do fronty, i = %d \n", actualCust->PID, i);
				incomingReq.Insert(actualCust);
				actualCust->Passivate();
			}
			else
			{
				printf("%lu: FTP - Apache - mam volno, i = %d \n", actualCust->PID, i);
				if (!incomingReq.Empty() && amIwait == 0)
				{
					amIwait++;
					printf("%lu: FTP - Apache - nekdo cekal, uvolnim ho, i = %d \n", actualCust->PID, i);
					(incomingReq.GetFirst())->Activate();
					incomingReq.Insert(actualCust);
					actualCust->Passivate();
				}
				else
					break;
			}
		}


		actualCust->Enter(actualCust->myCpu->processorsPower, 1);
		actualCust->Enter(mainProccessApache, 1);

		//pokud je zpracovavana doba vetsi nez maxCykluPerRound
		if (i != 0)
		{
			printf("%lu: FTP - Apache - cekam Round, i = %d \n", actualCust->PID, i);
			actualCust->Wait(actualCust->myCpu->countTime(actualCust->myCpu->maxCyclePerRound));
		}
		else
		{
			printf("%lu: FTP - Apache - cekam posledni, i = %d \n", actualCust->PID, i);
			actualCust->Wait(actualCust->myCpu->countTime(lastRound));
		}

		(new Request(actualCust->myCpu, actualCust->myApache, 2, actualCust->PID))->Activate(Time);

		printf("%lu: FTP - Apache - uvolnuji hlavni proces, procesor, i = %d \n", actualCust->PID, i);
		//odebereme procesor, hlavni proces apachu
		actualCust->Leave(mainProccessApache, 1);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);

		if (!incomingReq.Empty())
		{
			printf("%lu: FTP - Apache - uvolnuji prvni proces ve fronte, i = %d \n", actualCust->PID, i);
			(incomingReq.GetFirst())->Activate();
		}


	}
	(*actualCust->myCpu->hist)(Time - (actualCust->prichod));
}

//---------------------------------------------------------------

void Apache::createNewStreamProccess(StreamCustomer *actualCust)
{


	Stream++;

	unsigned long lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->myPar->timeCreateNewProcess, &lastRound);
	printf("%lu: STREAM - Apache pocet kol procesoru: %lu\n", actualCust->PID, round);

	int amIwait;

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;
		while (1)
		{
			if (actualCust->myCpu->processorsPower.Full() || mainProccessApache.Full())
			{
				amIwait++;
				printf("%lu: STREAM - Apache - jdu do fronty, i = %d \n", actualCust->PID, i);
				incomingReq.Insert(actualCust);
				actualCust->Passivate();
			}
			else
			{
				printf("%lu: STREAM - Apache - mam volno, i = %d \n", actualCust->PID, i);
				if (!incomingReq.Empty() && amIwait == 0)
				{
					amIwait++;
					printf("%lu: STREAM - Apache - nekdo cekal, uvolnim ho, i = %d \n", actualCust->PID, i);
					(incomingReq.GetFirst())->Activate();
					incomingReq.Insert(actualCust);
					actualCust->Passivate();
				}
				else
					break;
			}
		}


		actualCust->Enter(actualCust->myCpu->processorsPower, 1);
		actualCust->Enter(mainProccessApache, 1);

		//pokud je zpracovavana doba vetsi nez maxCykluPerRound
		if (i != 0)
		{
			printf("%lu: STREAM - Apache - cekam Round, i = %d \n", actualCust->PID, i);
			actualCust->Wait(actualCust->myCpu->countTime(actualCust->myCpu->maxCyclePerRound));
		}
		else
		{
			printf("%lu: STREAM - Apache - cekam posledni, i = %d \n", actualCust->PID, i);
			actualCust->Wait(actualCust->myCpu->countTime(lastRound));
		}

		(new Request(actualCust->myCpu, actualCust->myApache, 3, actualCust->PID))->Activate(Time);

		printf("%lu: STREAM - Apache - uvolnuji hlavni proces, procesor, i = %d \n", actualCust->PID, i);
		//odebereme procesor, hlavni proces apachu
		actualCust->Leave(mainProccessApache, 1);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);

		if (!incomingReq.Empty())
		{
			printf("%lu: STREAM - Apache - nekdo cekal, uvolnim ho, i = %d \n", actualCust->PID, i);
			(incomingReq.GetFirst())->Activate();
		}

	}
	(*actualCust->myCpu->hist)(Time - (actualCust->prichod));
}