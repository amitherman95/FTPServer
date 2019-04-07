/*
																				SlaveServer.cpp
																	Slave server implementation
Author:Amit Herman
amitherman@mail.tau.ac.il
*/

#include "SlaveServer.hpp"
#include "MasterServer.hpp"


SlaveServer::~SlaveServer() {
	socketClient.close();
}

void SlaveServer::setRootDir(const QString &rootPath) {
	interface_rootDir->setRootPath(rootPath);
}
void SlaveServer::setArg_username(const QString &username) {
	loginArgUsername = username;
}
void SlaveServer::setArg_Password(const QString &password) {
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

void SlaveServer::sendMessage( FTPReply reply) {

}


void SlaveServer::ControlThread() {
	boost::asio::mutable_buffer buffer;
	boost::system::error_code ignored_error;
	std::string commandLineTerminal;
	size_t sizeReceived=0;

	try {
			boost::asio::write(socketClient, boost::asio::buffer("220 Welcome"), ignored_error);
			while (1) {
				sizeReceived = boost::asio::read(socketClient, buffer);
				
			}
	}catch (boost::system::system_error &e) {
			cerr << "Error " << std::dec << e.code() << ":" << e.what();
			threadPI.detach();
			parentMaster->removeSlave(this);
			return;
	}
	
	
	
}

SlaveServer::SlaveServer(MasterServer*lpParent, tcp::socket& acceptedClientSocket) :parentMaster(lpParent),
																															socketClient(std::move(acceptedClientSocket)) {

	/*We transfer ownership to the the member socket of this class*/

	/*Initialize the thread by move operator*/
	threadPI = std::thread{ &SlaveServer::ControlThread, this };
	}

void SlaveServer::streamToTerminal(const char *lp_buffer, size_t sizeData, std::string &destTerminal) {
	const char LF = '\n'; //Line feed
	const char CR = '\r';// Carriage return
	auto it = destTerminal.end();// The Iterator represesnts the carrier of the terminal

	//since boost::mutable_buffer doesnt have iterators we'll just use regular loop
	for (int i = 0; i < sizeData; i++) {
		switch (lp_buffer[i]) {
		case(CR):
			

			}
	}

}