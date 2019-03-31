/*
																SlaveServer.hpp
															Slave server header
Author:Amit Herman
*/
#include "qstring.h"
#include "User.hpp"
#include <QtWidgets/QFileSystemModel>
#include <QtNetwork/qtcpserver.h>
#include "MasterServer.hpp"
#include <thread>

#ifndef SLAVE_SERVER_H
#define SLAVE_SERVER_H

class SlaveServer {

		/*Constants*/
public:
	static const int state_LoggedOut = 0;
	static const int state_LoggedIn = 1;
	static const int state_EnterPass = 2;
	static const int state_ExpectRenameTo = 3;

		/*Members*/
private:
	QString loginArgUsername;
	QString loginArgPassword;
	User *user=nullptr;
	MasterServer*parentMaster = nullptr;
/**<Protocol Interpreter thread, receive commands from client*/
	std::thread threadPI;
	QTcpSocket* socketClient = nullptr;
//*<Root directory access interface
	QFileSystemModel filesystem;
	int serverState = state_LoggedOut;

		/*Methods*/
	void setRootDir(QDir rootPath);
	void setArg_username(QString username);
	void setArg_Password(QString password);
	bool interpretCmd();
};
#endif
