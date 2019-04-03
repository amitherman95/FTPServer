/*
																		SlaveServer.cpp
															Slave server implementation
Author:Amit Herman
amitherman@mail.tau.ac.il
*/

#include "SlaveServer.hpp"
#include "MasterServer.hpp"


SlaveServer::~SlaveServer() {
	socketClient->close();
}

void SlaveServer::setRootDir(const QString &rootPath) {
	interface_rootDir.setRootPath(rootPath);
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
void SlaveServer::setSocket(QTcpSocket*lpClientSock) {
	socketClient = lpClientSock;
}
int SlaveServer::getState() {
	return serverState;
}
void SlaveServer::setState(const int state) {
	serverState = state;
}

void SlaveServer::sendMessage(FTPReply reply) {
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << std::dec << reply.get_code() << " " << reply.get_msg().toStdString().c_str()	 << '\n';
	while (socketClient->flush()) {}
}

SlaveServer::SlaveServer(MasterServer*lpParent, QTcpSocket*lpClientSock):socketClient(lpClientSock), parentMaster(lpParent)
{}