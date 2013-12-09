
#include "parseParam.h"

ParseParam::ParseParam(std::string fileName)
{
	err = "";
	myFile.open(fileName.c_str());
	parseFile();
	period = 0;
}

ParseParam::~ParseParam()
{
	myFile.close();
}

void ParseParam::parseFile()
{
	std::string readLine = "";
	if (!(myFile.is_open()))
	{
		std::cout << "Nepodarilo se otevrit soubor\n";
		return;
	}

	getline(myFile, readLine); //nacteme //INITTIME

	getline(myFile, readLine); //startTime
	startTime = splitConvert(readLine);
	if (startTime == 0)
		err += "Chyba v startTime\n";

	getline(myFile, readLine); //endTime
	endTime = splitConvert(readLine);
	if (endTime == 0)
		err += "Chyba v endTime\n";

	getline(myFile, readLine); //nacteme prazdny radek
	getline(myFile, readLine); //nacteme //CPU

	getline(myFile, readLine); //pocet procesoru
	processorCpu = splitConvert(readLine);
	if (processorCpu == 0)
		err += "Chyba v poctu procesoru\n";

	getline(myFile, readLine); //jadra procesoru
	coreCpu = splitConvert(readLine);
	if (coreCpu == 0)
		err += "Chyba v jadrech procesoru\n";
	
	getline(myFile, readLine); //vlakna procesoru
	threadsCpu = splitConvert(readLine);
	if (threadsCpu == 0)
		err += "Chyba v jadrech procesoru\n";

	getline(myFile, readLine); //frekvence procesoru
	frequencyCpu = splitConvert(readLine);
	if (frequencyCpu == 0)
		err += "Chyba ve frekvenci procesoru\n";

	getline(myFile, readLine); //cyclePerByte procesoru
	cyclePerByteCpu = splitConvert(readLine);
	if (cyclePerByteCpu == 0)
		err += "Chyba v cyclePerByte procesoru\n";

	getline(myFile, readLine); //maxCyclePerRound procesoru
	maxCyclePerRoundCpu = splitConvert(readLine);
	if (maxCyclePerRoundCpu == 0)
		err += "Chyba v maxCyclePerRoundCpu procesoru\n";

	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //RAM

	getline(myFile, readLine); //accessTimeRam Ram
	accessTimeRam = splitConvert(readLine);
	if (accessTimeRam == 0)
		err += "Chyba v accessTimeRam Ram\n";

	getline(myFile, readLine); //throughputRam Ram
	throughputRam = splitConvert(readLine);
	if (throughputRam == 0)
		err += "Chyba v throughputRam Ram\n";

	throughputRam = throughputRam / 1000;

	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //HDD

	getline(myFile, readLine); //accessTimeHdd HDD
	accessTimeHdd = splitConvert(readLine);
	if (accessTimeHdd == 0)
		err += "Chyba v accessTimeHdd HDD\n";

	getline(myFile, readLine); //countHdd HDD
	countHdd = splitConvert(readLine);
	if (countHdd == 0)
		err += "Chyba v countHdd HDD\n";

	getline(myFile, readLine); //speedOfReadHdd  HDD
	speedOfReadHdd = splitConvert(readLine);
	if (speedOfReadHdd == 0)
		err += "Chyba v speedOfReadHdd  HDD\n";


	getline(myFile, readLine); //speedOfWriteHdd  HDD
	speedOfWriteHdd = splitConvert(readLine);
	if (speedOfWriteHdd == 0)
		err += "Chyba v speedOfWriteHdd HDD\n";


	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //HTTP

	getline(myFile, readLine); //sizeHeaderHttp  HTTP
	sizeHeaderHttp = splitConvert(readLine);
	if (sizeHeaderHttp == 0)
		err += "Chyba v sizeHeaderHttp HTTP\n";

	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //EMAIL

	getline(myFile, readLine); //generateEmail0-4 EMAIL
	generateEmail = splitConvert(readLine);
	if (generateEmail == 0)
		err += "Chyba v generateEmail0-4 EMAIL\n";



	getline(myFile, readLine); //listEmailSizeEmail EMAIL
	listEmailSizeEmail = splitConvert(readLine);
	if (listEmailSizeEmail == 0)
		err += "Chyba v listEmailSizeEmail EMAIL\n";

	getline(myFile, readLine); //oneEmailSizeEmail EMAIL
	oneEmailSizeEmail = splitConvert(readLine);
	if (oneEmailSizeEmail == 0)
		err += "Chyba v oneEmailSizeEmail EMAIL\n";

	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //FTP

	getline(myFile, readLine); //generateFtp0-4Ftp
	generateFtp = splitConvert(readLine);
	if (generateFtp == 0)
		err += "Chyba v generateFtp 0-4 FTP\n";


	getline(myFile, readLine); //sizeDemandFileFtp FTP
	sizeDemandFileFtp = splitConvert(readLine);
	if (sizeDemandFileFtp == 0)
		err += "Chyba v sizeDemandFileFtp FTP\n";

	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //STREAM

	getline(myFile, readLine); //generateFtp0-4 STREAM
	generateStream = splitConvert(readLine);
	if (generateStream == 0)
		err += "Chyba v generateStream 0-4 STREAM\n";

	getline(myFile, readLine); //averageVideoStream STREAM
	averageVideoStream = splitConvert(readLine);
	if (averageVideoStream == 0)
		err += "Chyba v averageVideoStream STREAM\n";

	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //NETWORK

	getline(myFile, readLine); //capacityNetwork NETWORK
	capacityNetwork = splitConvert(readLine);
	if (capacityNetwork == 0)
		err += "Chyba v capacityNetwork NETWORK\n";

	getline(myFile, readLine); //prazdne misto
	getline(myFile, readLine); //APACHE

	getline(myFile, readLine); //timeCreateNewProcess APACHE
	timeCreateNewProcess = splitConvert(readLine);
	if (timeCreateNewProcess == 0)
		err += "Chyba v timeCreateNewProcess APACHE\n";




}

unsigned long ParseParam::splitConvert(std::string readLine)
{
	size_t found = readLine.find_last_of("=");
	std::string size = readLine.substr(found + 1);
	//printf("%s\n",size.c_str());
	return strtoul(size.c_str(), NULL, 0);

}