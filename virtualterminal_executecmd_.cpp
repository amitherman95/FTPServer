/*
/	 Filename:virtualterminal_executecmd_.cpp
/	 Description:extends VirtualTerminal.cpp for a specific long function executeCmd
/  Author:Amit Herman
*/
#include "VirtualTerminal.hpp"
#include "SlaveServer.hpp"
#include "ftpcmds.hpp"

/*Case Insensitive compare*/
bool cmp_Insenitive(const string &str1, const string &str2) {
	return stricmp(str1.c_str(), str2.c_str()) == 0;
}

/*Instruct the slave server what need to be done*/
void Terminal::executeCmd(const vector<string> &cmdParts){
	if (cmp_Insenitive(cmdParts[0],FTP::cmdUSER)) {
			parent->execCmdUser(cmdParts);
	}else if (cmp_Insenitive(cmdParts[0], FTP::cmdPASS)) {
			parent->execCmdPass(cmdParts);
	}else {
			parent->sendReply(500, "Command unrecognized");
	}
}

