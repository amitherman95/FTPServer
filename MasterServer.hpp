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
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "User.hpp"
#include "SlaveServer.hpp"
#include <queue>
#include <mutex>
using boost::asio::ip::tcp;

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
	//QTcpServer MainSocket;
	QXmlStreamReader xmlConfig;
	bool error;
	std::list<User> listUsers;
	std::list<std::unique_ptr<SlaveServer>> listClients;//*<Critical zone
	mutex locker;
	boost::asio::io_context io_context;
	unique_ptr<tcp::acceptor> acceptor;
	std::thread threadMasterThread;

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
/*cleans SlaveServer from the lise once it disconnects*/
	void removeSlave(SlaveServer*client);
	void lockMutex();
	void unlockMutex();

	/**
	*Exceptions:Problems with xml syntax
	*						problems with element data
	*           problem with with the file itself
	*\return True if error has occured, false otherwise
	*/
	bool loadConfig(const QString &configFilename);
	void executeMainThread();

private:
	bool insertNewClient( tcp::socket& clientSocket);
	void loadSettings();
	void setError(bool err);
	void loadUsers();
	void sendData( tcp::socket &clientSocket, const char*data, int dataLen);
	/*Master Thread, accept connections*/
	void MasterThread();

};
#endif