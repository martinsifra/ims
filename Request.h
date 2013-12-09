
#ifndef REQUEST_H
#define	REQUEST_H

#include "simlib.h"
#include "cpu.h"
#include "stdio.h"
#include <vector>
#include "apache.h"

class Cpu;
class Apache;


class Request : public Process {
public:
	Request(Cpu * cpu, Apache *apache, int typeReq, unsigned long mPID);
	virtual ~Request();

	//promenne
	Cpu *myCpu;
	Apache *myApache;
	double prichod;
	unsigned long PID;
	unsigned long headerSize;
	

	 std::vector<std::string> typReq;
	 
	 int typeVideo;

	//funkce
	void Behavior();
	void parseHeaderReq();
	
	//EMAILY
	//zobrazime hlavni stranku s emailama
	void viewListEmail();
	//rozhodnu se, co budu chtit provadet
	void viewEmail();
	//ctu emailu a odepisuji
	void actionInEmail();
	
	//FTP
	void findReqFile();
	void uploadFile();
	void downloadFile();
	
	//STREAM
	void watchVideo();
	
	//1 - EMAIL, 2 - FTP, 3 - STREAM
	int type;

private:

	
	

};

#endif	/* REQUEST_H */

