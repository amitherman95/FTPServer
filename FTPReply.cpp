/*
																			FTPReply.cpp
																FTP reply implementation
Author:Amit Herman
*/

#include "FTPReply.hpp"
#include <string.h>

FTPReply::FTPReply(int reply_code, const QString& msg) {
	code = reply_code;
	message = msg;
}

FTPReply::FTPReply(const FTPReply &src) {

	this->code = src.code;
	this->message = src.message;
}

FTPReply::FTPReply():code(0){
}


int FTPReply::get_code() {
	return code;
}
QString FTPReply::get_msg() {
	return message;
}