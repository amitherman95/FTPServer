/*
																			FTPReply.cpp
																FTP reply implementation
Author:Amit Herman
*/

#include "FTPReply.hpp"
FTPReply::FTPReply(int reply_code, const std::string msg) {
	code = reply_code;
	message = msg;
}

FTPReply::FTPReply(const FTPReply &src) {

	this->code = src.code;
	this->message = src.message;
}

FTPReply::FTPReply():code(0){}