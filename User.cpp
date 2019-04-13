/*
*																		User.cpp
*														User class implementation
*
* Author:Amit Herman
*
*/
#include "user.hpp"

User::User(): canWrite(false), canRead(false), canDelFiles(false), canManipulateDirs(false) {}

User::User(const std::string &username, const std::string &password, bool read ,
	bool write  ,bool delFiles, bool manipulateDirs ) {

	this->username = username;
	this->password = password;
	canRead = read;
	canWrite = write;
	canDelFiles = delFiles;
	canManipulateDirs = manipulateDirs;
	}

/* move ctor, used whenever we insert an element to a list*/
User::User(const User&src) {
	username = src.username;
	password = src.password;
	rootdir = src.rootdir;
	canRead = src.canRead;
	canWrite = src.canWrite;
	canDelFiles = src.canDelFiles;
	canManipulateDirs = src.canManipulateDirs;
}

User::User(User&& src) noexcept{
	username = src.username;
	password = src.password;
	rootdir = src.rootdir;
	canRead = src.canRead;
	canWrite = src.canWrite;
	canDelFiles = src.canDelFiles;
	canManipulateDirs = src.canManipulateDirs;

	src.username.clear();
	src.password.clear();

}

bool User::isPassRight(const std::string &argPass) {
	return password == argPass;
}

bool User:: isUser(const std::string &argUsername) {
	return username.compare(argUsername)==0;
}

void User::setPass(const QString &pass) {
	password = pass.toStdString();
}
void User::setUsername(const QString &user) {
	username = user.toStdString();
}
void User::setRead(bool read) {
	canRead = read;
}
void User::setWrite(bool write) {
	canWrite = write;
}
void User::setDel(bool del) {
	canDelFiles = del;
}
void User::setManDir(bool manDir) {
	canManipulateDirs = manDir;
}
void User::setRootDir(const QString &rootDir) {
	rootdir = rootDir;
}

QString User::getRootDir() {
	return rootdir;
}

bool User::getCanRead() {
	return canRead;
}

bool User::getCanWrite() {
	return canWrite;
}
bool User::getCanDel() {
	return canDelFiles;
}
bool User::getCanManDir() {
	return canManipulateDirs;
}