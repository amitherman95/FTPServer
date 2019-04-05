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
	FTPReply message(220, "Welcome\n");
	sendMessage(message);
	parentMaster->removeSlave(this);
	return;
}

SlaveServer::SlaveServer(MasterServer*lpParent, tcp::socket& acceptedClientSocket) :parentMaster(lpParent),
socketClient(io_context) {
	/*We transfer ownership to the the member socket of this class*/
	socketClient=std::move(acceptedClientSocket);
	/*Initialize the thread by move operator*/
	threadPI = std::thread{ &SlaveServer::ControlThread, this };
	}