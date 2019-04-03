/*
																	FTPReply.hpp
																FTP reply header
Author:Amit Herman

FTPReply objects are simple object which hold a string and a number to indicate the reply code.
*/

#ifndef FTP_REPLY_H
#define FTP_REPLY_H

#include <iostream>
#include <qstring.h>
using namespace std;

class FTPReply {
public:
	FTPReply(int reply_code, const QString& msg);
	FTPReply(const FTPReply &src);
	FTPReply();
	int get_code();
	QString get_msg();

private:
	int code;
	QString message;
};

#endif
