#include "VirtualTerminal.hpp"
#include "SlaveServer.hpp"
#include "ftpcmds.hpp"

/*Case insensitive compare as required bt rfc959*/
bool cmp_Insenitive(const string &str1, const string &str2) {
	return stricmp(str1.c_str(), str2.c_str()) == 0;
}

/*Instruct the slave server what need to be done*/
void Terminal::executeCmd(const vector<string> &cmdParts) {
	if (cmp_Insenitive(cmdParts[0], FTP::cmdUSER)) {
			parent->execCmdUser(cmdParts);
				
	}else if (cmp_Insenitive(cmdParts[0], FTP::cmdPASS)) {
			parent->execCmdPass(cmdParts);

	}else if(cmp_Insenitive(cmdParts[0], FTP::cmdNOOP)){
			parent->execCmdNoop(cmdParts);

	}else if(cmp_Insenitive(cmdParts[0], FTP::cmdMODE)){
			parent->execCmdMode(cmdParts);

	}else if(cmp_Insenitive(cmdParts[0], FTP::cmdSTRU)){
			parent->execCmdStructure(cmdParts);

	}else if(cmp_Insenitive(cmdParts[0], FTP::cmdPWD)){
			parent->execCmdPrintDirectory(cmdParts);

	}else if(cmp_Insenitive(cmdParts[0], FTP::cmdCWD)){
			parent->execCmdChangeDirectory(cmdParts);

	}else if(cmp_Insenitive(cmdParts[0], FTP::cmdCDUP)){
		parent->execCmdChangeDirUp(cmdParts);

	}else if(cmp_Insenitive(cmdParts[0], FTP::cmdPASV)) {
		parent->execCmdPassive(cmdParts);

	} else {
		parent->sendReply(500, "Command unrecognized");
	}



}