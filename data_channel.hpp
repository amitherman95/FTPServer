#ifndef _DATA_CHANNEL_HPP
#define _DATA_CHANNEL_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include "qdir.h"


//Forward decleration
class SlaveServer;

using namespace std;
using boost::asio::ip::tcp;	
using namespace boost::asio;

class DataChannel {
	
				/*Constants*/
public:
	static const int modePassive = 0;
	static const int modeActive = 1;
	static const int status_Not_Connected = 0;
	static const int status_Connected_Idle = 1;
	static const int status_Conneceted_inProgress = 2;
	static const int ftpDataPort = 20;

						/*Members*/
private:
	SlaveServer * parent;
	tcp::endpoint remoteHost;
	int status = status_Not_Connected;
	int mode;
	bool flagAbort;
	thread threadDataChannel;
	fstream streamFile;
	boost::asio::io_context io_context;
	tcp::socket socketData;
	tcp::acceptor acceptorData;
	QDir filepath;
	tcp::endpoint endPoint;
	int LastThreadReturnCode;
				/*Methods*/
public:
	void setStatus(int status);
	int getStatus();
	bool connectToHost();
	void setDataMode(int mode);
	int getDataMode();
	void setRemoteHostAddress(const string &stringAddress);
	void startUploading(const string &data);
	void startListening();
	/*Constructors and Destructors*/
	DataChannel();
	~DataChannel();

	/*Thread Functions*/
	bool download();
	void startUploading_list(iostream &stream);
	void upload(iostream &stream);
	void listen();
};


#endif