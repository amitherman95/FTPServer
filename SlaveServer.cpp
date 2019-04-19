/*
																					SlaveServer.cpp
																		Slave server implementation
Author:Amit Herman
amitherman@mail.tau.ac.il
*/

#include "SlaveServer.hpp"
#include "MasterServer.hpp"
#include "ftpcmds.hpp"
#include <boost/lexical_cast.hpp>

SlaveServer::~SlaveServer() {
	socketClient.close();
}

void SlaveServer::setRootDir(const QString &rootPath) {
	currentDir.setBasePath(rootPath);
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
	//vector<unsigned char> bytesBuffer;
	string buff;
	boost::system::error_code ec;
	
	size_t sizeReceived=0;

	//bytesBuffer.resize(buffer_size);
	buff.resize(buffer_size);
	try {
			sendReply(220, "Welcome");
			while (1) {
				sizeReceived = socketClient.read_some(boost::asio::buffer(buff));
				terminal.streamIntoTerminal(buff);
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
	/*Initialize the thread by move operator*/
	threadPI = std::thread{ &SlaveServer::ControlThread, this };
	}


void SlaveServer::sendReply(int code, const string&raw_message) {
	const string crlf = "\r\n";
	stringbuf message;
	ostream stream(&message);
	stream << std::dec << code << " " << raw_message << crlf;
	boost::asio::write(socketClient, boost::asio::buffer(message.str()));
}

void SlaveServer::sendReply(int code) {
	const string crlf = "\r\n";
	string message;
	message = boost::lexical_cast<string>(code) + crlf;
	boost::asio::write(socketClient, boost::asio::buffer(message));
}



void SlaveServer::removeServer() {
	threadPI.detach();
	parentMaster->removeSlave(this);
}



