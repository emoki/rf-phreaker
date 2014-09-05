/*
 * NMEAParser.cpp
 *
 *  Created on: Aug 12, 2014
 *      Author: me
 */

#include "NMEAParser.h"
#include <sstream>
#include <iostream>

using namespace std;

namespace rf_phreaker { namespace gps_comm {


NMEACommand::NMEACommand() : isvalid(false){

}
NMEACommand::NMEACommand(string text) : isvalid(false){
	isvalid = parseText(text);
}
NMEACommand::~NMEACommand(){

}
bool NMEACommand::valid(){
	return isvalid;
}

bool NMEACommand::parseText(string txt){
	text = txt;

	if(text[0] != '$'){
		return false;
	}

	//get rid of first '$'
	txt = txt.substr(1,txt.size()-1);

	size_t comma = txt.find(',');
	if(comma == string::npos){	//comma not found, but there is name...
													// the received data must just be the name
		if(txt.size() > 0)
		{
			name = txt;
			return true;
		}
		else
		{
			return false;		//it is a '$' with no information
		}
		//return true;
	}

	if(comma == 0){
		return false;		//"$," case
	}


	name = txt.substr(0,comma);		//name should not include first comma

	if(comma+1 == txt.size()){		//comma is the last character/only comma
		parameters.push_back("");
		return true;				//weird but still valid
	}


	//move to data after first comma
	txt = txt.substr(comma+1, txt.size()-(comma+1) );

	//parse parameters according to csv
	istringstream f(txt);
	string s;
	while (getline(f, s, ',')) {
		//cout << s << endl;
		parameters.push_back(s);
	}


	//above line parsing does not add a blank parameter if there is a comma at the end...
	// so do it here.
	if(txt[txt.size()-1] == ','){
		//cout << "NMEA parser Warning: extra comma at end of sentence, but no information...?" << endl;
		parameters.push_back("");
	}
	else
	{

		//possible checksum at end...
		size_t checki = parameters[parameters.size()-1].find('*');
		if(checki != string::npos){
			string last = parameters[parameters.size()-1];
			parameters[parameters.size()-1] = last.substr(0,checki);
			if(checki == last.size()-1){
				//.. '*' is last character... just ignore it
				//cout << "NMEA parser Warning: checksum '*' character at end, but no  data." << endl;
			}else{
				checksum = last.substr(checki+1, last.size()-checki);		//extract checksum without '*'
				//cout << "NMEA parser Info: found checksum. (\"*" << checksum << "\")" << endl;
			}
		}
	}

	return true;

}



NMEAParser::NMEAParser() : log(false){
	//newline = "\r\n";

}

NMEAParser::~NMEAParser() {
	// TODO Auto-generated destructor stub
}


void NMEAParser::setCommandHandler(std::string cmdKey, std::function<void(NMEACommand)> handler){
	std::pair<string, function<void(NMEACommand)>> entry(cmdKey, handler);
	eventTable.insert(entry);
	//eventTable.insert({cmdKey, handler});
}
void NMEAParser::parseByte(uint8_t b){
	if(b == '\n'){
		if( *(buffer.end()-1) == '\r'){
			handleTextCommand(buffer.substr(0,buffer.size()-1));
		}
		else
		{
			if(log){
				cout << "NMEA parse Warning: malformed newline, missing carriage return (\\r) " << endl;
			}
			handleTextCommand(buffer.substr(0,buffer.size()));
		}
		buffer = "";
	}else{
		buffer.push_back(b);
	}
}

// takes a complete NMEA string and gets the data bits from it,
// calls the corresponding handler in eventTable, based on the 5 letter sentence code (.name)
void NMEAParser::handleTextCommand(std::string cmd){
	if(log){
		cout << "NMEA parse Info: received new NMEA string. (\"" << cmd << "\")" << endl;
	}

	NMEACommand nmea(cmd);
	if(!nmea.valid()){
		//break some stuff
		//throw NMEAParseError("NMEA parse error: " + cmd);
		if(!log){
			return;
		}

		if(nmea.text.size() > 10){
			cout << "NMEA parse Error: Invalid text. (\"" << nmea.text.substr(0,10) << "...\")" << endl;
		}
		else{
			cout << "NMEA parse Error: Invalid text. (\"" << nmea.text.substr(0,nmea.text.size()) << "\")" << endl;
		}
		return;
	}

	if(log){		//shows parsed params...
		cout << "\tParse Success >> name: " << nmea.name
				<< "\tchecksum: " << nmea.checksum
				<< "\tparams: [";
		if(nmea.parameters.size() > 0){
			for(size_t i = 0; i < nmea.parameters.size()-1; i++){
				cout << "\"" << nmea.parameters[i] << "\",";
			}
			cout << "\"" << nmea.parameters[nmea.parameters.size()-1] << "\"";
		}else{cout << "none";}
		cout << "]" << endl;
	}

	//call the "any command" event handler
	if(onCommand.target_type().hash_code() != typeid(void).hash_code()){
			onCommand(nmea);
	}

	//ok, dispatch events based on map entries
	function<void(NMEACommand)> handler = eventTable[nmea.name];
	if(handler.target_type().hash_code() != typeid(void).hash_code()){
		handler(nmea);
	}
	else
	{
		if(log)
		{
			cout << "NMEA parse Warning: null event handler for type (name: \"" << nmea.name << "\")" << endl;
		}
	}

}

void NMEAParser_test(){
}


}} 
