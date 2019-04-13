/*
/																							VirtualTerminal.cpp
/																				Virtual Terminal implementation
/	Author:Amit Herman
/	amitherman@mail.tau.ac.il
/**/

#include "VirtualTerminal.hpp"
#include "SlaveServer.hpp"
#include  <boost/algorithm/string.hpp>


Terminal::Terminal(SlaveServer*lp_parent) :parent(lp_parent), stream(&bufferTerminal){

}

void Terminal::streamIntoTerminal(const string &buffer) {
	
	vector<string> cmdSplitVector;
	for (int i = 0; i < buffer.size(); i++) {
		switch (buffer[i]) {
		case LF:
				cmdSplitVector=processCommandLine();
				executeCmd(cmdSplitVector);
				bufferTerminal.str(""); //clear buffer
				break;
		case IP:
				executeRemoteInterrupt();
				break;
		case CR:
				bufferTerminal.pubseekpos(0);
				break;
		case BS:
				bufferTerminal.pubseekoff(-1, ios_base::cur);
				break;
		default:
				stream << buffer[i];
				break;
		}
	}
}


vector<string> Terminal::processCommandLine() {
	vector<string> cmdSplit;
	boost::regex regex("( |\t)+");
	string temp = bufferTerminal.str();
	boost::trim(temp);
	iter_regexToken it(temp.begin(), temp .end(), regex, -1);
	iter_regexToken iterRegexEnd;

	for (; it != iterRegexEnd; ++it) {
		cmdSplit.push_back(*it);
	}
	return cmdSplit;
}

void Terminal::executeRemoteInterrupt(){

}

