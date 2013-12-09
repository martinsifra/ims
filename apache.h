#ifndef APACHE_H
#define APACHE_H

#include "simlib.h"
#include "emailCustomer.h"
#include "ftpCustomer.h"
#include "streamCustomer.h"
#include "Request.h" 
#include <stdio.h>

class EmailCustomer;
class FtpCustomer;
class StreamCustomer;

class Apache {
public:
	Apache(int countMainProcces); //konstruktor
	~Apache(); //destruktor


	/**
	 * @brief Funkce simuluje vytvoreni (fork) v apache pozadavek na cteni
	 * @param actualCust aktualni zpracovavany proces
	 */
	void createNewEmailProccess(EmailCustomer *actualCust);
	void createNewFtpProccess(FtpCustomer *actualCust);
	void createNewStreamProccess(StreamCustomer *actualCust);

	Store mainProccessApache; //hlavni proces, ktery bezi furt

	Queue incomingReq;



	unsigned long Email;
	unsigned long Stream;
	unsigned long Ftp;


	unsigned long EmailP;
	unsigned long StreamP;
	unsigned long FtpP;


private:


};

#endif //APACHE_H