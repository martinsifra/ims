#include "emailCustomer.h"

EmailCustomer::EmailCustomer(Apache *apache, Cpu *cpu)
{
	myApache = apache;
	myCpu = cpu;

	//zde se priradi nahodna velikost hlavicky
	headerSize = 800;

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
			Wait((double)myCpu->maxCyclePerRound);
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
	unsigned long round = myCpu->numberRound(myCpu->countTime(56000), &lastRound);
	for (unsigned long i = round; i >= 0; i--)
	{
		Enter(myCpu->processorsPower, 1);
		//provadim zpracovani hlavicky pozadavku
		if (i != 0)
		{
			Wait((double)myCpu->maxCyclePerRound);
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
	myCpu->emailCustomerRead(this, 56000);

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
	unsigned long size = 5000;

	for (int i = 1; i <= numberEmails; i++)
	{
		myCpu->emailCustomerRead(this, size);

		//bude tam priloha?
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			//budeme ji chtit stahovat? 
			if (myCpu->myRandValue(100, 1) > 10)
			{
				//zde musime uvest velikost prumerne prilohy
				//atachFileSizes
				size = 20000;
				myCpu->emailCustomerRead(this, size);
			}
		}


		//odpovidame nebo piseme novy email
		if (myCpu->myRandValue(100, 1) <= 90)
		{
			if (myCpu->myRandValue(100, 1) <= 10)
			{
				//email + priloha = generovat
				size = 1000 + 5000;
				myCpu->emailCustomerWrite(this, size);
			}
			else
			{
				size = 1000;
				myCpu->emailCustomerWrite(this, size);
			}
		}

		//mazeme email
		if (myCpu->myRandValue(100, 1) <= 10)
		{

			size = 100;
			myCpu->emailCustomerRead(this, size);
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
	Activate(Time + Exponential(ROZLOZENIGENEROVANI)); // zde se aktivuje


}