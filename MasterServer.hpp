/*
*																			  	MasterServer.h
*																		Master Server class header
*
* Author:Amit Herman
* 
*/	

#ifndef MASTER_SERVER_H
#define MASTER_SERVER_H


#include <QtCore/qxmlstream.h>
#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include <iostream>
#include <thread>
#include "User.hpp"
#include "SlaveServer.hpp"

using namespace std;
/**
* \classMasterServer
*		Description: Master Server represents the process that listens on port 21(ftp)
*							 accepted clients,and spawns SlaveServer which handle the control and data 
*							 sessions for one client.

*/

class MasterServer:public QObject {
	
	Q_OBJECT
	/*	Members		*/
private:
	int maxClients;
	bool limitClients; //*<Indicates whether there is a limit to the number of clients
	QString msgWelcome;
	int serverState=masterStopped;
	QTcpServer MainSocket;
	QXmlStreamReader xmlConfig;
	bool error;
	list<User> listUsers;
	list<unique_ptr<SlaveServer>> listClients;

	
	/*	Constants	*/
public:
	static const int masterActive = 1;
	static const int masterStopped = 0;
	static const int ftpPort = 21;
	static const int ftpDataPot = 20;

	/*	methods	*/
public:
	/**
	* Constructor
	* \param pathConfig the path of the xml config file
	*/
	MasterServer(const QString &pathConfig);

	/**
	* Default Constructor
	* loads default settings for the server
	*/
	MasterServer();

	/**
	* Set a limit to the number of simultaneous connections
	*\param max - Client limit
	*/
	void setMaxClients(int max);

	/**
	* Indicates whether there should be a limit
	* in case of true setMaxClients becomes irrelevant
	*/
	void setLimitClients(bool ans);

	/**
	* Welcome message is the message a client gets when he connects to the server
	*/
	void setWelcomeMsg(const QString &Message);

	int getMaxClients();
	bool areClientsLimited();
	bool startServer();
	void stopServer();
	QString getWelcomeMsg();
	bool hasError();

	/**
	*Exceptions:Problems with xml syntax
	*						problems with element data
	*           problem with with the file itself
	*\return True if error has occured, false otherwise
	*/
	bool loadConfig(const QString &configFilename);

private:
	/**
	* Main Server thread
	* accepts connection requests and spawn new
	*/
	void MasterThread();
	bool insertNewClient(QTcpSocket* clientSocket);
	void loadSettings();
	void setError(bool err);
	void loadUsers();
	void sendData(QTcpSocket*Client, const char*data, int dataLen);
public slots:
	bool acceptConnection();

};
#endif