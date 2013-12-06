#include "emailCustomer.h"

EmailCustomer::EmailCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;

	//zde se priradi nahodna velikost hlavicky
	headerSize = myCpu->myPar->sizeHeaderHttp;

}

//------------------------------------------

EmailCustomer::~EmailCustomer()
{


}
//--------------------------------------------

void EmailCustomer::parseHeaderReq()
{
	printf("Zpracuji pozadavek - hlavicku\n");
	double lastRound;
	unsigned long round = myCpu->numberRound(myCpu->countTime(headerSize), &lastRound);
	for (unsigned long i = round; i >= 0; i--)
	{
		Enter(myCpu->processorsPower, 1);
		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			Wait((double) myCpu->maxCyclePerRound);
		}
		else
		{
			Wait(lastRound);
		}
		Leave(myCpu->processorsPower, 1);
	}
}
//--------------------------------------------

void EmailCustomer::emailAction()
{
	printf("Vystavuji seznam emailu\n");

	double lastRound;
	unsigned long round = myCpu->numberRound(myCpu->countTime(myCpu->myPar->listEmailSizeEmail), &lastRound);
	for (unsigned long i = round; i >= 0; i--)
	{
		Enter(myCpu->processorsPower, 1);
		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			Wait((double) myCpu->maxCyclePerRound);
		}
		else
		{
			Wait(lastRound);
		}
		Leave(myCpu->processorsPower, 1);
	}

}
//---------------------------------------------

void EmailCustomer::viewListEmail()
{
	//listEmailSize
	myCpu->emailCustomerRead(this, myCpu->myPar->listEmailSizeEmail);

}
//---------------------------------------------

void EmailCustomer::viewEmail()
{

	//*****zatim zde mam jenom nejake rozlozeni, zmenit ***********//
	if (myCpu->myRandValue(100, 1) <= 10)
	{
		//jenom jsem se mrkl, nasledne odchazim
		return;
	}
	else
	{
		actionInEmail();
	}
}
//---------------------------------------------

void EmailCustomer::actionInEmail()
{
	//vygenerujeme, kolik emailu budeme cist
	int numberEmails = myCpu->myRandValue(5, 1);
	//zde bude velikost 1 emailu, ktery se bude stahovat
	unsigned long size = myCpu->myPar->oneEmailSizeEmail;

	for (int i = 1; i <= numberEmails; i++)
	{
		parseHeaderReq();

		myCpu->emailCustomerRead(this, size);

		//bude tam priloha?
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			//budeme ji chtit stahovat? 
			if (myCpu->myRandValue(100, 1) > 10)
			{
				//zpracuji hlavicku pozadavku
				parseHeaderReq();
				//zde musime uvest velikost prumerne prilohy
				//atachFileSizes
				size = myCpu->myPar->attachFilesSizeEmail;
				myCpu->emailCustomerRead(this, size);
			}
		}


		//odpovidame nebo piseme novy email
		if (myCpu->myRandValue(100, 1) <= 90)
		{
			parseHeaderReq();
			if (myCpu->myRandValue(100, 1) <= 10)
			{
				//email + priloha = generovat
				size = myCpu->myPar->oneEmailSizeEmail + myCpu->myPar->attachFilesSizeEmail;
				myCpu->emailCustomerWrite(this, size);
			}
			else
			{
				size = myCpu->myPar->oneEmailSizeEmail;
				myCpu->emailCustomerWrite(this, size);
			}
		}

		//mazeme email
		parseHeaderReq();
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			size = myCpu->myPar->oneEmailSizeEmail;
			myCpu->emailCustomerWrite(this, size);
		}
	}


}


//---------------------------------------------

void EmailCustomer::Behavior()
{
	prichod = Time;
	//vytvarime novy proces
	myApache->createNewEmailProccess(this);

	//Zpracujeme hlavicku
	parseHeaderReq();

	//zobrazime si zakladni prehled emailu
	viewListEmail();

	//bude si uzivatel zobrazovat nejake emaily
	viewEmail();


	//precetly jsme emaily, odeslaly a tedka namodelovat sit kdyztak
}





//--------------------------------------------
//--------------------------------------------

GeneratorEmail::GeneratorEmail(Apache *apache, Cpu * cpu)
{
	myApache = apache;
	myCpu = cpu;

}
//--------------------------------------------

GeneratorEmail::~GeneratorEmail()
{



}

//--------------------------------------------

void GeneratorEmail::Behavior()
{ // --- behavior specification --- 

	(new EmailCustomer(myApache, myCpu))->Activate(); // novy email customer
	Activate(Time + Exponential(myCpu->myPar->generateEmail)); // zde se aktivuje


}