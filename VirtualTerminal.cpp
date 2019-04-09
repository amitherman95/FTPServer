/*
																							VirtualTerminal.cpp
																					Virtual Terminal implementation
Author:Amit Herman
amitherman@mail.tau.ac.il
/**/
#include "VirtualTerminal.hpp"
#include "SlaveServer.hpp"


Terminal::Terminal(SlaveServer*lp_parent) :parent(lp_parent){}

void Terminal::streamIntoTerminal(vector<unsigned char> buffer) {
	for (int i = 0; i < buffer.size(); i++) {
		switch (buffer[i]) {
		case LF:
				interpretCommandLine();
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


void Terminal::interpretCommandLine() {

	cout << this->terminal << endl;
}

void Terminal::executeRemoteInterrupt(){

}