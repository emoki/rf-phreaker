/*
 * NMEAParser.cpp
 *
 *  Created on: Aug 12, 2014
 *      Author: ck
 */

#include "NMEAParser.h"
#include "NumberConversion.h"
#include <sstream>
#include <iostream>

using namespace std;

namespace rf_phreaker { namespace gps_comm {


	// --------- NMEA SENTENCE --------------

NMEASentence::NMEASentence() : isvalid(false), calculatedChecksum(0), parsedChecksum(0){

}
NMEASentence::~NMEASentence(){

}
bool NMEASentence::valid(){
	return isvalid;
}
bool NMEASentence::checksumOK(){
	return (parsedChecksum != 0 && calculatedChecksum != 0)
		&&
		(parsedChecksum == calculatedChecksum);
}










	// --------- NMEA PARSER --------------



NMEAParser::NMEAParser() : log(false), maxbuffersize(NMEA_PARSER_MAX_BUFFER_SIZE){
	//newline = "\r\n";

}

NMEAParser::~NMEAParser() {
	// TODO Auto-generated destructor stub
}


void NMEAParser::setCommandHandler(std::string cmdKey, std::function<void(NMEASentence)> handler){
	eventTable.erase(cmdKey);

	//std::pair<string, function<void(NMEASentence)>> entry(cmdKey, handler);
	//eventTable.insert(entry);
	eventTable.insert({ cmdKey, handler });
}
void NMEAParser::parseByte(uint8_t b){
	if (b == '\n'){
		if (buffer.size() > 0  &&   *(buffer.end() - 1) == '\r'){
			handleTextCommand(buffer.substr(0, buffer.size() - 1));
		}
		else
		{
			if (log){
				cout << "NMEA parser Warning: malformed newline, missing carriage return (\\r) " << endl;
			}
			handleTextCommand(buffer.substr(0, buffer.size()));
		}
		buffer = "";
	}
	else{
		if (buffer.size() < maxbuffersize){
			buffer.push_back(b);
		}
		else {
			buffer.clear();		//clear the host buffer so it won't overflow.
		}
	}
}

// takes a complete NMEA string and gets the data bits from it,
// calls the corresponding handler in eventTable, based on the 5 letter sentence code (.name)
void NMEAParser::handleTextCommand(std::string cmd){

	if (cmd.size() == 0){
		if (log){
			cout << endl << " >> NMEA parser Info: Received new NMEA string. Blank -- Skipped processing." << endl;
		}
		return;
	}

	ios_base::fmtflags oldflags = cout.flags();

	if (log){
		cout << endl << " >> NMEA parser Info: Received new NMEA string. (\"" << cmd << "\")" << endl;
	}



	NMEASentence nmea;
	try{
		parseText(nmea, cmd);
	}
	catch (std::exception& e){
		string s = "NMEA Parse Error: Indexing error...";
		throw std::runtime_error(s + e.what());
	}
	cout.flags(oldflags);  //reset

	if (!nmea.valid()){
		if (!log){
			return;
		}

		if (nmea.text.size() > 10){
			cout << "NMEA parser Error: Invalid text. (\"" << nmea.text.substr(0, 10) << "...\")" << endl;
		}
		else{
			cout << "NMEA parser Error: Invalid text. (\"" << nmea.text << "\")" << endl;
		}
		return;
	}

	if (nmea.checksumOK()){

		if (log){		//shows parsed params...
			cout << "\tParse Success >> name: " << nmea.name
				<< "\tchecksum: 0x" << nmea.checksum
				<< "\tparams: [";
			if (nmea.parameters.size() > 0){
				for (size_t i = 0; i < nmea.parameters.size() - 1; i++){
					cout << "\"" << nmea.parameters[i] << "\",";
				}
				cout << "\"" << nmea.parameters[nmea.parameters.size() - 1] << "\"";
			}
			else{ cout << "none"; }
			cout << "]" << endl;
		}
	}
	else
	{
		if (log){
			cout << "\t Parse Failed >> Checksum is incorrect. [parsed: 0x"
				<< std::hex << (int)nmea.parsedChecksum << ", calculated: 0x"
				<< std::hex << (int)nmea.calculatedChecksum << "]" << endl;
		}
	}



	//ok, dispatch events based on map entries
	function<void(NMEASentence)> handler = eventTable[nmea.name];
	if (handler.target_type().hash_code() != typeid(void).hash_code()){
		if (log){
			cout << "NMEA parser Info: Calling specific event handler for sentence named \"" << nmea.name << "\"" << endl;
		}
		handler(nmea);
	}
	else
	{
		if (log)
		{
			cout << "NMEA parser Warning: null event handler for type (name: \"" << nmea.name << "\")" << endl;
		}
	}




	//call the "any command" event handler, even if invalid checksum for possible logging elsewhere.
	if (log){
		cout << "NMEA parser Info: Calling generic onCommand handler for sentence. [name: \"" << nmea.name << "\"]" << endl;
	}
	onCommand(nmea);

	cout.flags(oldflags);  //reset

}

// takes the string *between* the '$' and '*' in nmea sentence,
// then calculates a rolling XOR on the bytes
uint8_t NMEAParser::calculateChecksum(string s){
	uint8_t checksum = 0;
	for (size_t i = 0; i < s.size(); i++){
		checksum = checksum ^ s[i];
	}

	// will display the calculated checksum in hex
	//if(log)
	//{
	//	ios_base::fmtflags oldflags = cout.flags();
	//	cout << "NMEA parser Info: calculated CHECKSUM for \""  << s << "\": 0x" << std::hex << (int)checksum << endl;
	//	cout.flags(oldflags);  //reset
	//}
	return checksum;
}


void NMEAParser::parseText(NMEASentence& nmea, string txt){

	if (txt.size() == 0){
		nmea.isvalid = false;
		return;
	}


	nmea.text = txt; // save the received text of the sentence

	size_t startbyte = 0;		//will be index of first '$'
	size_t dollar = txt.find('$');
	if (dollar == string::npos){	//comma not found, but there is name...
		nmea.isvalid = false;

		return;
	}
	else
	{
		startbyte = dollar;
	}


	//get rid of first '$'
	txt = txt.substr(startbyte + 1);


	size_t checkstri = txt.find('*');
	if (checkstri != string::npos){
		nmea.calculatedChecksum = calculateChecksum(txt.substr(0, checkstri));
	}
	else
	{
		if (log){
			cout << "NMEA parser Error: No checksum information provided. Could not find '*'." << endl;
		}
	}


	size_t comma = txt.find(',');
	if (comma == string::npos){	//comma not found, but there is name...
		// the received data must just be the name
		if (txt.size() > 0)
		{
			nmea.name = txt;
			nmea.isvalid = true;
			return;
		}
		else
		{
			nmea.isvalid = false;
			return;		//it is a '$' with no information
		}
		//return true;
	}

	if (comma == 0){
		nmea.isvalid = false;
		return;		//"$," case
	}


	nmea.name = txt.substr(0, comma);		//name should not include first comma

	if (comma + 1 == txt.size()){		//comma is the last character/only comma
		nmea.parameters.push_back("");
		nmea.isvalid = true;
		return;						//not valid/standard.
	}


	//move to data after first comma
	txt = txt.substr(comma + 1, txt.size() - (comma + 1));

	//parser parameters according to csv
	istringstream f(txt);
	string s;
	while (getline(f, s, ',')) {
		//cout << s << endl;
		nmea.parameters.push_back(s);
	}


	//above line parsing does not add a blank parameter if there is a comma at the end...
	// so do it here.
	if (txt[txt.size() - 1] == ','){
		//cout << "NMEA parser Warning: extra comma at end of sentence, but no information...?" << endl;		// it's actually standard, if checksum is disabled
		nmea.parameters.push_back("");
	}
	else
	{

		//possible checksum at end...
		size_t checki = nmea.parameters[nmea.parameters.size() - 1].find('*');
		if (checki != string::npos){
			string last = nmea.parameters[nmea.parameters.size() - 1];
			nmea.parameters[nmea.parameters.size() - 1] = last.substr(0, checki);
			if (checki == last.size() - 1){
				//.. '*' is last character... just ignore it
				if (log)
				{
					cout << "NMEA parser Error: checksum '*' character at end, but no  data." << endl;
				}
			}
			else{
				nmea.checksum = last.substr(checki + 1, last.size() - checki);		//extract checksum without '*'
				if (log)
				{
					cout << "NMEA parser Info: found checksum. (\"*" << nmea.checksum << "\")" << endl;
				}

				try
				{
					nmea.parsedChecksum = (uint8_t)parseInt(nmea.checksum, 16);
				}
				catch(NumberConversionError &)
				{
					if (log){
						cout << "NMEA parser Error: parseInt() error. Parsed checksum string was not readable as hex. (\"" << nmea.checksum << "\")" << endl;
					}
				}
				if (log)
				{
					cout << "NMEA parser Info: Checksum OK? " << (nmea.checksumOK() ? "YES" : "NO") << "!" << endl;
				}

			}
		}
	}

	nmea.isvalid = true;
	return;

}



}} 
