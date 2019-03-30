/*
*																		User.cpp
*														User class implementation
*
* Author:Amit Herman
*
*/
#include "user.hpp"

User::User(): canWrite(false), canRead(false), canDelFiles(false), canManipulateDirs(false) {}

User::User(const QString &username, const QString &password, bool read ,
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

bool User::isPassRight(const QString &pass) {
	return password == pass;
}

bool User:: isUser(const QString &userName) {
	return username.compare(username)==0;
}

void User::setPass(const QString &pass) {
	password = pass;
}
void User::setUsername(const QString &user) {
	username = user;
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