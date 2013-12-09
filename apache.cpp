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

	int amIwait;

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;

		while (1)
		{
			if (actualCust->myCpu->processorsPower.Full() || mainProccessApache.Full())
			{
				amIwait++;
				incomingReq.Insert(actualCust);
				actualCust->Passivate();
			}
			else
			{
//				printf("%lu: EMAIL - Apache - mam volno, i = %d \n", actualCust->PID, i);
				if (!incomingReq.Empty() && amIwait == 0)
				{
					amIwait++;
//					printf("%lu: EMAIL - Apache - nekdo cekal, uvolnim ho, i = %d \n", actualCust->PID, i);
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
			actualCust->Wait(actualCust->myCpu->countTime(actualCust->myCpu->maxCyclePerRound));
		}
		else
		{
			actualCust->Wait(actualCust->myCpu->countTime(lastRound));
		}

		//ma byt Time v zavorce?
		(new Request(actualCust->myCpu, actualCust->myApache, 1, actualCust->PID))->Activate(Time);

		//odebereme procesor, hlavni proces apachu
		actualCust->Leave(mainProccessApache, 1);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);

		if (!incomingReq.Empty())
		{
			(incomingReq.GetFirst())->Activate();
		}


	}
	//(*actualCust->myCpu->histPozadavky)(Time - (actualCust->prichod));

}
//---------------------------------------------------------

void Apache::createNewFtpProccess(FtpCustomer *actualCust)
{

	Ftp++;


	unsigned long lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->myPar->timeCreateNewProcess, &lastRound);

	int amIwait;

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;
		while (1)
		{
			if (actualCust->myCpu->processorsPower.Full() || mainProccessApache.Full())
			{
				amIwait++;
				incomingReq.Insert(actualCust);
				actualCust->Passivate();
			}
			else
			{
				if (!incomingReq.Empty() && amIwait == 0)
				{
					amIwait++;
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
			actualCust->Wait(actualCust->myCpu->countTime(actualCust->myCpu->maxCyclePerRound));
		}
		else
		{
			actualCust->Wait(actualCust->myCpu->countTime(lastRound));
		}

		(new Request(actualCust->myCpu, actualCust->myApache, 2, actualCust->PID))->Activate(Time);

		//odebereme procesor, hlavni proces apachu
		actualCust->Leave(mainProccessApache, 1);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);

		if (!incomingReq.Empty())
		{
			(incomingReq.GetFirst())->Activate();
		}


	}
	//(*actualCust->myCpu->histPozadavky)(Time - (actualCust->prichod));
}

//---------------------------------------------------------------

void Apache::createNewStreamProccess(StreamCustomer *actualCust)
{


	Stream++;

	unsigned long lastRound;
	unsigned long round = actualCust->myCpu->numberRound(actualCust->myCpu->myPar->timeCreateNewProcess, &lastRound);

	int amIwait;

	for (int i = round; i >= 0; i--)
	{
		amIwait = 0;
		while (1)
		{
			if (actualCust->myCpu->processorsPower.Full() || mainProccessApache.Full())
			{
				amIwait++;
				incomingReq.Insert(actualCust);
				actualCust->Passivate();
			}
			else
			{
				if (!incomingReq.Empty() && amIwait == 0)
				{
					amIwait++;
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
			actualCust->Wait(actualCust->myCpu->countTime(actualCust->myCpu->maxCyclePerRound));
		}
		else
		{
			actualCust->Wait(actualCust->myCpu->countTime(lastRound));
		}

		(new Request(actualCust->myCpu, actualCust->myApache, 3, actualCust->PID))->Activate(Time);

		//odebereme procesor, hlavni proces apachu
		actualCust->Leave(mainProccessApache, 1);
		actualCust->Leave(actualCust->myCpu->processorsPower, 1);

		if (!incomingReq.Empty())
		{
			(incomingReq.GetFirst())->Activate();
		}

	}
	//(*actualCust->myCpu->histPozadavky)(Time - (actualCust->prichod));
}