/*
																SlaveServer.hpp
															Slave server header
Author:Amit Herman
*/

#ifndef SLAVE_SERVER_H
#define SLAVE_SERVER_H

/*Forward Decleration
'#include MasterServer' must be added to implementation*/
class MasterServer;

#include "qstring.h"
#include "User.hpp"
#include <QtWidgets/QFileSystemModel>
#include <QtNetwork/qtcpserver.h>
#include <thread>


/**\class SlaveServer class
*	Represents the connection to each client
	and handles user control.
*/
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
	//MasterServer* parentMaster = nullptr;
/**<Protocol Interpreter thread, receive commands from client*/
	std::thread threadPI;
	QTcpSocket* socketClient = nullptr;
//*<Root directory access interface
	QFileSystemModel filesystem;
	int serverState = state_LoggedOut;

			/*Methods*/

public:
/*Constructors and Destructor*/
	SlaveServer();
	SlaveServer(MasterServer*lpParent, QTcpSocket*lpClientSock);
	~SlaveServer();

/*Getters and setters*/
	void setRootDir(QDir rootPath);
	void setArg_username(const QString &username);
	void setArg_Password(const QString &password);
	void setParent(MasterServer*lpParent);
	void setSocket(QTcpSocket*lpClientSock);
	int getState();
	void setState(const int state);


public:
	bool interpretCmd();

	/**Slave Server thread
*	Implements the concept of Protocol Interpreter process,
	which listens for commands from client
*/
private:
	void ControlThread();

};

#endif
