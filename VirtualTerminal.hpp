/*
																						VirtualTerminal.hpp
																					Virtual Terminal headers																		
Author:Amit Herman
amitherman@mail.tau.ac.il
/**/

#ifndef VIRTUAL_TERMINAL_H_
#define VIRTUAL_TERMINAL_H_

#include <ostream>
#include <vector>
#include <boost/regex.hpp>
#include <sstream>
typedef boost::sregex_token_iterator iter_regexToken;
using namespace std;
/*Forward decleration
/	must add '#include "SlaveServer.hpp"' into implementation
/**/
class SlaveServer;


/**\class Terminal
Since the FTP protocol is based on the Telnet protocol, the ftp server implements virtual terminal in which the remote host
insert input as if it  is working with a real local terminal

The Virtual Terminal is implemented using std::string as the terminal, and std::string::iterator
as the the carrier of the of the terminal, thus the NVT(Network virtual terminal) follows all the basics of
the Telnet Protocol standard.
The terminal is responsible for telling the SlaveServer what appropriate action has to be taken.
*/
class Terminal {

			/*Constants*/
public:
	/*Since we dont need to implement all the protocol of telenet, we'll just
	/*handle the input that is relevant for modern FTP clients.
	/**/
	static const unsigned char CR = '\r';//*<Carriage return
	static const unsigned char LF = '\n'; //*<Line Feed
	static const unsigned char IP = 0x3; //*<interrupt process, this corresponds to ETX in ASCII code
	static const unsigned char BS = 0x8; //*<Backspace

			/*Members*/
private:
	std::stringbuf bufferTerminal;
	SlaveServer*parent;
	ostream stream;
	string lastCommand;

			/*Methods*/
public:
	Terminal(SlaveServer*lp_parent);
	~Terminal()=default;
	vector<string> processCommandLine();
	void streamIntoTerminal(const string &buffer);
	void executeRemoteInterrupt();
	void executeCmd(const vector<string> &cmdParts);
};

#endif