/*
																	FTPReply.hpp
																FTP reply header
Author:Amit Herman

FTPReply objects are simple object which hold a string and a number to indicate the reply code.
*/

#ifndef SLAVE_SERVER_H
#define SLAVE_SERVER_H
#include <iostream>

class FTPReply {
	FTPReply(int reply_code, const std::string message);
	FTPReply(const FTPReply &src);
	FTPReply();

private:
	int code;
	std::string message;
};

#endif
