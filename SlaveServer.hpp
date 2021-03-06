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
#include "VirtualTerminal.hpp"
#include "QDirExtended.hpp"
#include "data_channel.hpp"

using boost::asio::ip::tcp;


/**\class SlaveServer class
*	Represents the connection to each client
	and handles user control.	
*/
class SlaveServer:public QObject {
	Q_OBJECT
																		/*Constants*/
public:
	static const int state_LoggedOut = 0;
	static const int state_LoggedIn = 1;
	static const int state_EnterPass = 2;
	static const int state_ExpectRenameTo = 3;

																			/*Members*/
private:
	string loginArgUsername;
	string loginArgPassword;
	User *user=nullptr;
	MasterServer* parentMaster = nullptr;
/**<Protocol Interpreter thread, receive commands from client*/
	std::thread threadPI;
	tcp::socket socketClient;
//*<Root directory access interface
	QDirExtended currentDir;
	QFile fileToRename;
	int serverState = state_LoggedOut;
	boost::asio::io_context io_context;
	Terminal terminal;
	DataChannel dataChannel;
																	/*Methods*/

public:
			/*Constructors and Destructor*/
	SlaveServer()=delete;
	SlaveServer(MasterServer *lpParent, tcp::socket& acceptedClientSocket);
	~SlaveServer();

			/*Getters and setters*/
	void setRootDir(const QString &rootPath);
	void setArg_username(const string &username);
	void setArg_Password(const string &password);
	void setParent(MasterServer*lpParent);
	void setSocket( tcp::socket &acceptedClientSocket);
	int getState();
	void setState(const int state);
	void sendReply(int code, const string&message);
	void sendReply(int code);

													/*Access Control Commands*/
public:
	void execCmdUser(const vector<string> &cmdParts);
	void execCmdPass(const vector<string> &cmdParts);
	void execCmdNoop(const vector<string> &cmdParts);
	void execCmdMode(const vector<string> &cmdParts);
	void execCmdStructure(const vector<string> &cmdParts);
	void execCmdReinit(const vector<string> &cmdParts);
	void execCmdPrintDirectory(const vector<string> &cmdParts);
	void execCmdPassive(const vector<string> &cmdParts);
	void execCmdType(const vector<string> &cmdParts);

														/*Service Commands*/
	void execCmdChangeDirectory(const vector<string> &cmdParts);
	void execCmdChangeDirUp(const vector<string> &cmdParts);
	void execCmdList(const vector<string> &cmdParts);

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


};

#endif
