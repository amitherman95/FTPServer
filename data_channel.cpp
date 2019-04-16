/*
/																Data Channel Implementation
/
/		Author:Amit Herman
*/

#include "data_channel.hpp"
typedef boost::system::system_error boost_sysError;

DataChannel::DataChannel(): socketData(io_context), acceptorData(io_context, tcp::endpoint(tcp::v4(), ftpDataPort)) {

}
DataChannel::~DataChannel() {
	socketData.close();
}

void DataChannel::setStatus(int status) {
	this->status = status;
}


int DataChannel::getStatus() {
	return this->status;
}


bool DataChannel::listen() {
	try {
			acceptorData.accept(socketData);
	}catch (const boost_sysError &e) {
			return false;
	}
	return true;
}

void DataChannel::setDataMode(int mode) {
	this->mode = mode;
}



int DataChannel::getDataMode() {
	return this->mode;
}


void DataChannel::upload(const string &data) {

}