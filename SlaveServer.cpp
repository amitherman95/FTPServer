/*
																				SlaveServer.cpp
																	Slave server implementation
Author:Amit Herman
amitherman@mail.tau.ac.il
*/

#include "SlaveServer.hpp"
#include "MasterServer.hpp"
#include "ftpcmds.hpp"

SlaveServer::~SlaveServer() {
	socketClient.close();
}

void SlaveServer::setRootDir(const QString &rootPath) {
	interface_rootDir->setRootPath(rootPath);
}
void SlaveServer::setArg_username(const string &username) {
	loginArgUsername = username;
}
void SlaveServer::setArg_Password(const string &password) {
	loginArgPassword = password;
}
void SlaveServer::setParent(MasterServer*lpParent) {
	parentMaster = lpParent;
}
void SlaveServer::setSocket( tcp::socket &acceptedClientSocket) {
	this->socketClient = std::move(acceptedClientSocket);
}
int SlaveServer::getState() {
	return serverState;
}
void SlaveServer::setState(const int state) {
	serverState = state;
}


void SlaveServer::ControlThread() {
	const int buffer_size = 1; //stream one by one
	vector<unsigned char> bytesBuffer;
	boost::system::error_code ec;
	
	size_t sizeReceived=0;

	bytesBuffer.resize(buffer_size);
	try {
			sendReply(220, "Welcome");
			while (1) {
				sizeReceived = socketClient.read_some(boost::asio::buffer(bytesBuffer));
				terminal.streamIntoTerminal(bytesBuffer);
			}
	}catch (const boost::system::system_error &e) {
			cerr << "Error " << std::dec << e.code() << ":" << e.what();
			removeServer();
			return;
	}
	
}

SlaveServer::SlaveServer(MasterServer*lpParent, tcp::socket& acceptedClientSocket) :parentMaster(lpParent),
																															socketClient(std::move(acceptedClientSocket)),
																															terminal(this) {

	/*We transfer ownership to the the member socket of this class*/

	/*Initialize the thread by move operator*/
	threadPI = std::thread{ &SlaveServer::ControlThread, this };

	}


void SlaveServer::sendReply(int code, const string&raw_message) {
	string message;
	ostringstream stream(message);
	stream << std::dec << code << " " << raw_message <<endl;
	boost::asio::write(socketClient, boost::asio::buffer(message));
}


void SlaveServer::removeServer() {
	threadPI.detach();
	parentMaster->removeSlave(this);
}



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
			if (user = NULL) {
					sendReply(530, "No such username");
			}else if (user->isPassRight(cmdParts.at(2))){
					this->user = user;
					sendReply(230, "Logged in");
			}
	}
}