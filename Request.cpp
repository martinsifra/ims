
#include "Request.h"

Request::Request(Cpu *cpu, int typeReq, unsigned long mPID)
{
	myCpu = cpu;
	type = typeReq;

	if (typeReq == 1) //EMAIL
		PID = mPID;
	else if (typeReq == 2) //FTP
		PID = mPID;
	else // STREAM
		PID = mPID;

	typReq.push_back("");
	typReq.push_back("EMAIL");
	typReq.push_back("FTP");
	typReq.push_back("STREAM");

	headerSize = myCpu->myPar->sizeHeaderHttp;

	//= { "", "EMAIL", "FTP", "STREAM"};

}
//-----------------------------------------------------

Request::~Request()
{
}
//-----------------------------------------------------

void Request::parseHeaderReq()
{
	printf("%lu: %s - HEADReq, %lu \n", PID, (typReq[type]).c_str(), headerSize);
	double lastRound;
	//zjistime pocet kol procesoru
	unsigned long round = myCpu->numberRound(myCpu->countTime(headerSize), &lastRound);

	//kolikrat jsem cekal
	int amIwait;

	for (int i = round; i >= 0; i--)
	{
		//ukazovatko, jestli budu davat prednost ostatnim procesum
		amIwait = 0;

		while (1)
		{
			if (myCpu->processorsPower.Full())
			{
				amIwait++;
				printf("%lu: %s - HEADReq - neni procesor - jdu do fronty, i = %d \n", PID, (typReq[type]).c_str(), i);
				myCpu->waitingProcess.Insert(this);
				Passivate();
			}
			else
			{
				printf("%lu: %s - HEADReq - volno , i = %d \n", PID, (typReq[type]).c_str(), i);
				if (!myCpu->waitingProcess.Empty() && amIwait == 0)
				{
					printf("%lu: %s - HEADReq - nekdo cekal, uvolnim ho, i = %d \n", PID, (typReq[type]).c_str(), i);
					(myCpu->waitingProcess.GetFirst())->Activate();
					myCpu->waitingProcess.Insert(this);
					Passivate();
				}
				else
					break;
			}
		}


		printf("%lu: %s - HEADReq - zabiram procesor, i = %d \n", PID, (typReq[type]).c_str(), i);
		//zabiram si procesor
		Enter(myCpu->processorsPower, 1);

		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			printf("%lu: %s - HEADReq - cekam round, i = %d \n", PID, (typReq[type]).c_str(), i);
			Wait((double) myCpu->maxCyclePerRound);
		}
		else
		{
			printf("%lu: %s - HEADReq - cekam zbytek, i = %d \n", PID, (typReq[type]).c_str(), i);
			Wait(lastRound);
		}
		Leave(myCpu->processorsPower, 1);

		if (!myCpu->waitingProcess.Empty())
		{
			printf("%lu: %s - HEADReq - nekdo cekal, uvolnim ho, i = %d \n", PID, (typReq[type]).c_str(), i);
			(myCpu->waitingProcess.GetFirst())->Activate();
		}

	}



}
//--------------------------------------------------

void Request::viewListEmail()
{
	printf("%lu: Email - Zobrazuji seznam emailu \n", PID);
	myCpu->requestRead(this, myCpu->myPar->listEmailSizeEmail);
}
//---------------------------------------------------

void Request::viewEmail()
{

	//*****zatim zde mam jenom nejake rozlozeni, zmenit ***********//
	if (myCpu->myRandValue(100, 1) <= 10)
	{
		//jenom jsem se mrkl, nasledne odchazim
		printf("%lu: %s - Nic nechci, odchazim\n", PID, (typReq[type]).c_str());
	}
	else
	{
		actionInEmail();
	}
}
//-----------------------------------------------------

void Request::actionInEmail()
{
	//vygenerujeme, kolik emailu budeme cist
	int numberEmails = myCpu->myRandValue(3, 1);

	//zde bude velikost 1 emailu, ktery se bude stahovat
	unsigned long size = myCpu->myPar->oneEmailSizeEmail;

	for (int i = 1; i <= numberEmails; i++)
	{
		printf("%lu: Email - pozadavek na email %i \n", PID, i);
		parseHeaderReq();

		//ctu email prumerne velikosti
		printf("%lu: Email - ctu email %i \n", PID, i);
		myCpu->requestRead(this, size);

		//bude tam priloha?
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			//budeme ji chtit stahovat? 
			if (myCpu->myRandValue(100, 1) > 10)
			{
				//zpracuji hlavicku pozadavku na prilohu
				printf("%lu: Email - pozadavek na prilohu emailu %i \n", PID, i);
				parseHeaderReq();

				//atachFileSizes
				size = myCpu->myPar->attachFilesSizeEmail;

				printf("%lu: Email - ctu prilohu email %i \n", PID, i);
				//stahuji prilohu
				myCpu->requestRead(this, size);
			}
		}


		//odpovidame nebo piseme novy email
		if (myCpu->myRandValue(100, 1) <= 90)
		{
			//zpracovavam hlavicku
			printf("%lu: Email - pozadavek na psani email %i \n", PID, i);
			parseHeaderReq();

			if (myCpu->myRandValue(100, 1) <= 10)
			{
				// odesilam (zapisuji na HDD)  velikost email + priloha 
				printf("%lu: Email - psani email %i i priloha  \n", PID, i);
				size = myCpu->myPar->oneEmailSizeEmail + myCpu->myPar->attachFilesSizeEmail;
				myCpu->requestWrite(this, size);
			}
			else
			{
				printf("%lu: Email - psani email %i  \n", PID, i);
				size = myCpu->myPar->oneEmailSizeEmail;

				//odesilam (zapisuji na HDD) jenom email
				myCpu->requestWrite(this, size);
			}
		}

		//mazani email
		parseHeaderReq();

		//mazeme jenom v 10procentech
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			size = myCpu->myPar->oneEmailSizeEmail;
			//mazu disk
			printf("%lu: Email - mazu email %i i priloha  \n", PID, i);
			myCpu->requestWrite(this, size);
		}
	}


}

//--------------------------------------------

void Request::uploadFile()
{
	if (myCpu->myRandValue(100, 1) <= 90)
	{
		int numberFile = myCpu->myRandValue(5, 1);
		//zde bude velikost 1 souboru, ktery se bude stahovat

		for (int i = 1; i <= numberFile; i++)
		{
			parseHeaderReq();
			myCpu->requestWrite(this, myCpu->myPar->averageFileFtp);
		}
	}
}
//--------------------------------------------

void Request::downloadFile()
{
	if (myCpu->myRandValue(100, 1) <= 60)
	{
		int numberFile = myCpu->myRandValue(5, 1);


		for (int i = 1; i <= numberFile; i++)
		{
			parseHeaderReq();
			myCpu->requestRead(this, myCpu->myPar->averageFileFtp);
		}
	}
}
//-----------------------------------------------------
void Request::findReqFile()
{

	//nez se doklikame k pozadovanemu souboru
	myCpu->requestRead(this, myCpu->myPar->sizeDemandFileFtp);

}
//------------------------------------------------------
void Request::watchVideo()
{
	int numberVideo = myCpu->myRandValue(5, 1);
	//zde bude velikost 1 souboru, ktery se bude stahovat

	for (int i = 1; i <= numberVideo; i++)
	{
		parseHeaderReq();
		myCpu->requestRead(this, myCpu->myPar->averageVideoStream);
	}

}
//-----------------------------------------------------
void Request::Behavior()
{
	if (type == 1) //pokud je to email
	{
		prichod = Time;

		printf("%lu: Novy Email\n", PID);

		parseHeaderReq();

		//zobrazime si zakladni prehled emailu
		viewListEmail();

		//bude si uzivatel zobrazovat nejake emaily
		viewEmail();

	}
	else if (type == 2) //pokud je to FTP
	{
		prichod = Time;
		printf("%lu: Nove FTP\n", PID);
		parseHeaderReq();

		findReqFile();

		uploadFile();

		downloadFile();

	}
	else // pokud je to STREAM
	{
		prichod = Time;
		printf("%lu: Novy Stream\n", PID);
		parseHeaderReq();

    watchVideo();
	}



}
