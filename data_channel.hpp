#ifndef _DATA_CHANNEL_HPP
#define _DATA_CHANNEL_HPP
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <thread>

using namespace std;
using boost::asio::ip::tcp;

class DataChannel {
	
				/*Constants*/
public:
	static const int modePassive = 0;
	static const int modeActive = 1;
	static const int statusIdle = 0;
	static const int statusInProgress = 1;

						/*Members*/
private:
	string remoteHostIP;
	int remoteHostPort;
	int status;
	int mode;
	bool flagAbort;
	thread threadDataChannel;
	fstream streamFile;
	tcp::socket socketData;
	boost::asio::io_context io_context;
	string filePath;

				/*Methods*/
public:
	void setStatus(int status);
	int getStatus();
	bool listen();
	bool connectToHost();
	void setDataMode(int mode);
	int getDataMode();
	bool upload();

	/*Thread Functions*/
	bool upload();
	bool download();
};
#endif