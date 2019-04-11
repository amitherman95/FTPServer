/*
/																							VirtualTerminal.cpp
/																				Virtual Terminal implementation
/	Author:Amit Herman
/	amitherman@mail.tau.ac.il
/**/
#include "VirtualTerminal.hpp"
#include "SlaveServer.hpp"
#include  <boost/algorithm/string.hpp>


Terminal::Terminal(SlaveServer*lp_parent) :parent(lp_parent){}

void Terminal::streamIntoTerminal(const vector<unsigned char>buffer) {
	vector<string> cmdSplitVector;
	for (int i = 0; i < buffer.size(); i++) {
		switch (buffer[i]) {
		case LF:
				cmdSplitVector=processCommandLine();
				executeCmd(cmdSplitVector);
				terminal.clear();
				break;
		case IP:
				executeRemoteInterrupt();
				break;
		default:
				terminal.push_back(buffer[i]);
				break;
		}
	}
}


vector<string> Terminal::processCommandLine() {
	vector<string> cmdSplit;
	boost::regex regex("( |\t)+");
	string temp = terminal;
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

