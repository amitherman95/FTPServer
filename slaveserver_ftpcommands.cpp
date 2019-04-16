#include "SlaveServer.hpp"
#include "MasterServer.hpp"
#include "ftpcmds.hpp"


void SlaveServer::execCmdUser(const vector<string> &cmdParts) {
	if (cmdParts.size() != 2) {
			sendReply(501, "Syntax error");
	}else {
			setArg_username(cmdParts.at(1));
	}
}

void SlaveServer::execCmdPass(const vector<string> &cmdParts) {
	User*user;
	if (cmdParts.size() != 2) {
			sendReply(501, "Syntax error");
	}else {
			user = parentMaster->findUser(loginArgUsername);
			if (user == NULL) {
					sendReply(530, "No such username");
			}else if (user->isPassRight(cmdParts.at(1))){
					this->user = user;
			/*Assuming the path is correct*/
					this->setRootDir(user->getRootDir());
					sendReply(230, "Logged in");
			}else {
					sendReply(530, "Wrong password");
			}
	}
	loginArgUsername.clear();
}


void SlaveServer::execCmdNoop(const vector<string> &cmdParts) {
	if (cmdParts.size() != 1) {
			sendReply(501, "Syntax error");
	}else {
			sendReply(200, "OK");
	}
}

void SlaveServer::execCmdMode(const vector<string> &cmdParts) {
	if (cmdParts.size() != 1) {
		sendReply(501, "Syntax error");
	} else {
		if (cmdParts.at(1) == "f"|| cmdParts.at(1) == "F" ) {
				sendReply(200, "OK");
		}else {
			sendReply(501, "This server supports only stream mode");
		}
	}
}


void SlaveServer::execCmdStructure(const vector<string> &cmdParts) {
	if (cmdParts.size() != 1) {
			sendReply(501, "Syntax error");
	} else {
		if (cmdParts.at(1) == "s"|| cmdParts.at(1) == "S") {
			sendReply(200, "OK");
		} else {
			sendReply(501, "This server supports only stream mode");
		}
	}
}

void SlaveServer::execCmdPrintDirectory(const vector<string> &cmdParts) {
	string path;
	if (cmdParts.size() != 2) {
		sendReply(501, "Syntax error");
	} else if (this->getState() == 0) {
		sendReply(530, "Not logged in");
	} else {
		path =  "\"" +  currentDir.relativePath()+ "\"";
		sendReply(267, path);
	}
}



void SlaveServer::execCmdChangeDirectory(const vector<string> &cmdParts) {
	if (cmdParts.size() != 2) {
		sendReply(501, "Syntax error");
		return;
	} else if (this->getState() == 0) {
		sendReply(530, "Not logged in");
		return;
	}
	if (currentDir.cd(QString::fromStdString(cmdParts.at(1)))){
		sendReply(250, "Okay");
	}else {
		sendReply(550, "Directory does not exist");
	}
}


void SlaveServer::execCmdChangeDirUp(const vector<string> &cmdParts) {
	if (cmdParts.size() != 1) {
		sendReply(501, "Syntax error");
		return;
	}else if (this->getState() == 0) {
		sendReply(530, "Not logged in");
		return;
	}
	currentDir.cdup();
	sendReply(250, "Okay");
}


void SlaveServer::execCmdPassive(const vector<string> &cmdParts) {


}