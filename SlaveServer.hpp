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
#include <QtWidgets/qfilesystemmodel.h>
#include <boost/asio.hpp>
#include <thread>
#include "FTPReply.hpp"

using boost::asio::ip::tcp;

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
	MasterServer* parentMaster = nullptr;
/**<Protocol Interpreter thread, receive commands from client*/
	std::thread threadPI;
	tcp::socket socketClient;
//*<Root directory access interface
	QFileSystemModel* interface_rootDir;
	int serverState = state_LoggedOut;
	boost::asio::io_context io_context;
																	/*Methods*/

public:
			/*Constructors and Destructor*/
	SlaveServer()=delete;
	SlaveServer(MasterServer *lpParent, tcp::socket& acceptedClientSocket);
	~SlaveServer();

			/*Getters and setters*/
	void setRootDir(const QString &rootPath);
	void setArg_username(const QString &username);
	void setArg_Password(const QString &password);
	void setParent(MasterServer*lpParent);
	void setSocket( tcp::socket &acceptedClientSocket);
	int getState();
	void setState(const int state);
	void sendMessage(FTPReply reply);
	
			/**Access and commands*/
public:
	bool interpretCmd();

	/**In case the client disconnect, this function call removeClient from the master server and removes the client
	*from the list of
	*/
	void removeServer();

	/**Slave Server thread
*	Implements the concept of Protocol Interpreter process,
	which listens for commands from client
*/
private:
	void ControlThread();

	/*We go through the buffer, char by char, and append it to Dest
		When we stream CRLF char, this is a command line, and therefore we instruct the Protocol interpreter to
		ensure the command is valid and execute it
		the string object destTerminal acts excatly like computer terminal/
	*/
	void streamToTerminal(const char *lp_bufferData,size_t sizeData , std::string &destTerminal);

};

#endif
