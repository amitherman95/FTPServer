#ifndef _DATA_CHANNEL_HPP
#define _DATA_CHANNEL_HPP
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <thread>
#include "qdir.h"

using namespace std;
using boost::asio::ip::tcp;	
using namespace boost::asio;


class DataChannel {
	
				/*Constants*/
public:
	static const int modePassive = 0;
	static const int modeActive = 1;
	static const int status_Not_Conneceted = 0;
	static const int status_Connected_Idle = 1;
	static const int status_Conneceted_inProgress = 2;
	static const int ftpDataPort = 20;

						/*Members*/
private:
	tcp::endpoint remoteHost;
	int status = status_Not_Conneceted;
	int mode;
	bool flagAbort;
	thread threadDataChannel;
	fstream streamFile;
	boost::asio::io_context io_context;
	tcp::socket socketData;
	tcp::acceptor acceptorDataChannel;
	QDir filepath;
	tcp::endpoint endPoint;
	int LastThreadReturnCode;
				/*Methods*/
public:
	void setStatus(int status);
	int getStatus();
	bool listen();
	bool connectToHost();
	void setDataMode(int mode);
	int getDataMode();
	void setRemoteHostAddress(const string &stringAddress);
	void startUploading(const string &data);
	/*Constructors and Destructors*/
	DataChannel();
	~DataChannel();

	/*Thread Functions*/
	bool upload();
	void upload(const string &data);
	bool download();
};


#endif