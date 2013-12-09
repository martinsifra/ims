
#include "Request.h"

Request::Request(Cpu *cpu, Apache *apache, int typeReq, unsigned long mPID)
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
 
	myApache = apache;
	//= { "", "EMAIL", "FTP", "STREAM"};

}
//-----------------------------------------------------

Request::~Request()
{
}
//-----------------------------------------------------

void Request::parseHeaderReq()
{
	unsigned long lastRound;
	//zjistime pocet kol procesoru
	unsigned long round = myCpu->numberRound(myCpu->countCycle(headerSize), &lastRound);

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
				myCpu->waitingProcess.Insert(this);
				Passivate();
			}
			else
			{
				if (!myCpu->waitingProcess.Empty() && amIwait == 0)
				{
					amIwait++;
					(myCpu->waitingProcess.GetFirst())->Activate();
					myCpu->waitingProcess.Insert(this);
					Passivate();
				}
				else
					break;
			}
		}

		//zabiram si procesor
		Enter(myCpu->processorsPower, 1);

		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			Wait(myCpu->countTime(myCpu->maxCyclePerRound));
		}
		else
		{
			Wait(myCpu->countTime(lastRound));
		}

		myCpu->leaveCpuStartNext(this);

	}



}
//--------------------------------------------------

void Request::viewListEmail()
{
	myCpu->requestRead(this, myCpu->myPar->listEmailSizeEmail);
}
//---------------------------------------------------

void Request::viewEmail()
{

	//*****zatim zde mam jenom nejake rozlozeni, zmenit ***********//
	if (myCpu->myRandValue(100, 1) <= 10)
	{
		//jenom jsem se mrkl, nasledne odchazim
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
	unsigned long size;

	for (int i = 1; i <= numberEmails; i++)
	{
		parseHeaderReq();

		size = Normal(myCpu->myPar->oneEmailSizeEmail, 1);
		//ctu email prumerne velikosti
		myCpu->requestRead(this, size);

		//bude tam priloha?
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			//budeme ji chtit stahovat? 
			if (myCpu->myRandValue(100, 1) > 10)
			{
				//zpracuji hlavicku pozadavku na prilohu
				parseHeaderReq();

				//atachFileSizes
				size = Exponential(0.00000555);

				//stahuji prilohu
				myCpu->requestRead(this, size);
			}
		}


		//odpovidame nebo piseme novy email
		if (myCpu->myRandValue(100, 1) <= 90)
		{
			//zpracovavam hlavicku
			parseHeaderReq();

			if (myCpu->myRandValue(100, 1) <= 10)
			{
				// odesilam (zapisuji na HDD)  velikost email + priloha 
				size = Normal(myCpu->myPar->oneEmailSizeEmail, 1) + Exponential(0.00000555);
				myCpu->requestWrite(this, size);
			}
			else
			{
				size = Normal(myCpu->myPar->oneEmailSizeEmail, 1);

				//odesilam (zapisuji na HDD) jenom email
				myCpu->requestWrite(this, size);
			}
		}

		//mazani email
		parseHeaderReq();

		//mazeme jenom v 10procentech
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			size = Normal(myCpu->myPar->oneEmailSizeEmail, 1);
			//mazu disk
			myCpu->requestWrite(this, size);
		}
	}


}

//--------------------------------------------

void Request::uploadFile()
{
	double sizeFile;
	if (myCpu->myRandValue(100, 1) <= 90)
	{
		int numberFile = myCpu->myRandValue(2, 1);
		//zde bude velikost 1 souboru, ktery se bude stahovat

		for (int i = 1; i <= numberFile; i++)
		{
			parseHeaderReq();
			sizeFile = Exponential(0.000043);
			myCpu->requestWrite(this, sizeFile);
		}
	}
}
//--------------------------------------------

void Request::downloadFile()
{
	if (myCpu->myRandValue(100, 1) <= 60)
	{
		int numberFile = myCpu->myRandValue(2, 1);

    double sizeFile;
		for (int i = 1; i <= numberFile; i++)
		{
			parseHeaderReq();
			sizeFile = Exponential(0.0000165);
			myCpu->requestRead(this, sizeFile);
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
	unsigned long videoSize;
	unsigned long longVideo;
	for (int i = 1; i <= numberVideo; i++)
	{
		parseHeaderReq();
		longVideo = Normal(myCpu->myPar->averageVideoStream, 1);
		videoSize = longVideo * typeVideo;
		myCpu->requestRead(this, videoSize);
	}

}
//-----------------------------------------------------

void Request::Behavior()
{
	prichod = Time;
	if (type == 1) //pokud je to email
	{
		parseHeaderReq();

		//zobrazime si zakladni prehled emailu
		viewListEmail();

		//bude si uzivatel zobrazovat nejake emaily
		viewEmail();

		myCpu->Email << (Time - prichod) << "\n";
	}
	else if (type == 2) //pokud je to FTP
	{
//		printf("%lu: Nove FTP\n", PID);
		parseHeaderReq();

		findReqFile();

		uploadFile();

		downloadFile();

		myCpu->Ftp << (Time - prichod) << "\n";

	}
	else // pokud je to STREAM
	{
		//vygenerujeme, jake ma uzivatel pripojeni - podle toho zvolime 
		int value = myCpu->myRandValue(100, 1);
		if (value <= 45)
		{
			typeVideo = 22142400;
		}
		else if (value > 45 && value <= 70)
		{
			typeVideo = 8310400;
		}
		else if (value > 70 && value <= 86)
		{
			typeVideo = 22142400;
		}
		else if (value > 86 && value <= 92)
		{
			typeVideo = 22142400;
		}
		else
		{
			typeVideo = 2726720;
		}

//		printf("%lu: Novy Stream\n", PID);
		parseHeaderReq();

		watchVideo();
		myCpu->Stream << (Time - prichod) << "\n";
	}
  
	(*myCpu->histPozadavkyReq)(Time - (prichod));




}
