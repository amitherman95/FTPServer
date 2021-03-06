/*
*																					MasterServer.cpp
*																	Master Server class implementation
*
* Author:Amit Herman
*
*/

#include "MasterServer.hpp"
#include <qfile.h>
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <iterator>

MasterServer::MasterServer() :maxClients(10), limitClients(true), msgWelcome("FTP Server by Amit Herman"),
error(false) {
	
}

MasterServer::MasterServer(const QString &pathConfig) {
	error=loadConfig(pathConfig);
}

void MasterServer::setMaxClients(int max) {
	maxClients = max;
}
void MasterServer::setLimitClients(bool ans) {
	limitClients = ans;
}
void MasterServer::setWelcomeMsg(const QString& Message) {
	msgWelcome = Message;
}

int MasterServer::getMaxClients() {
	return maxClients;
}

bool MasterServer::areClientsLimited() {
	return limitClients;
}

QString MasterServer::getWelcomeMsg() {
	return msgWelcome;
}

bool MasterServer::loadConfig(const QString &filename) {
	
	QFile file;
	file.setFileName(filename);
	if (!file.open(QIODevice::ReadOnly)) {
		std::cerr << "Error, Could not open file";
		setError(true);
		return true;
	}
	xmlConfig.setDevice(&file);
	while (!xmlConfig.atEnd()) {

		//Handles the "general" part of the config file
		if(xmlConfig.name().toString().compare("general",Qt::CaseInsensitive)==0&& xmlConfig.isStartElement() ){
				try {
						loadSettings();
				}catch (std::exception &e) {
						std::cerr << e.what() << std::endl;
						file.close();
						setError(true);
						return true;
				}
		}
		//Handles the "general" part of the config file
		if (xmlConfig.name().toString().compare("users", Qt::CaseInsensitive) == 0 && xmlConfig.isStartElement()) {
			try {
				loadUsers();
			} catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
				file.close();
				setError(true);
				return true;
			}
		}
		xmlConfig.readNextStartElement();
	}

	file.close();
	setError(false);
	return false;
}

void MasterServer::loadSettings() {
	bool ok = true;
	QString name;
	name = xmlConfig.name().toString();
	while (name.compare("general")!=0 || !xmlConfig.isEndElement()) {
		if (name == "limitClients") {
			this->limitClients = xmlConfig.readElementText().compare("true", Qt::CaseInsensitive);
		}
		else if (name.compare("maxClients", Qt::CaseInsensitive) == 0) {
			this->maxClients = xmlConfig.readElementText().toInt(&ok);
			if (!ok) throw std::invalid_argument("Error at XML:Element:\"maxClients\"data should have only numbers");
		}
		else if (name.compare("welcome_msg", Qt::CaseInsensitive) == 0) {
			this->msgWelcome = xmlConfig.readElementText();
		}
		else if (xmlConfig.atEnd())
			throw(std::runtime_error("Invalid XML"));
		xmlConfig.readNextStartElement();
		name = xmlConfig.name().toString();
	}
	
}

void MasterServer::setError(bool flagError) {
	error = flagError;
}

bool MasterServer::hasError() {
	return error;
}

void MasterServer::loadUsers() {
	QString name;
	User temp;
	bool flagInUserSubRoot = false;
	name = xmlConfig.name().toString();
	while (name.compare("users") != 0 || !xmlConfig.isEndElement()) { //The loop ends at </users> end tag
		if (name.compare("user", Qt::CaseInsensitive) == 0 && xmlConfig.isStartElement()) {
				if(flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				flagInUserSubRoot = true;
		} else if (name.compare("user", Qt::CaseInsensitive) == 0 && xmlConfig.isEndElement()) {
				if (!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				flagInUserSubRoot = false;
				listUsers.push_back(temp);
		} else if (xmlConfig.atEnd()) {
				throw(std::runtime_error("Invalid XML"));
		} else if (name.compare("username", Qt::CaseInsensitive) == 0) {
				if(!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				temp.setUsername(xmlConfig.readElementText());
		} else if (name.compare("password", Qt::CaseInsensitive) == 0) {
				if (!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				temp.setPass(xmlConfig.readElementText());
		} else if (name.compare("rootdir", Qt::CaseInsensitive) == 0) {
				if (!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				temp.setRootDir(xmlConfig.readElementText());
		} else if (name.compare("write", Qt::CaseInsensitive) == 0) {
				if (!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				temp.setWrite(xmlConfig.readElementText() == "true");
		} else if (name.compare("read", Qt::CaseInsensitive) == 0) {
				if (!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				temp.setRead(xmlConfig.readElementText() == "true");
		} else if (name.compare("delete_files", Qt::CaseInsensitive) == 0) {
				if (!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				temp.setDel(xmlConfig.readElementText().compare("true", Qt::CaseInsensitive)==0);
		} else if (name.compare("manipulate_folders", Qt::CaseInsensitive) == 0) {
				if (!flagInUserSubRoot) throw(std::runtime_error("Invalid XML"));
				temp.setManDir(xmlConfig.readElementText().compare("true", Qt::CaseInsensitive) == 0);
		}
		xmlConfig.readNextStartElement();
		name = xmlConfig.name().toString();
	}	
}



bool MasterServer::startServer() {
	if (hasError()) {
			std::cerr << "Error, Unable to start\n";
			return false;
	}
	if (this->serverState == MasterServer::masterStopped) {
			this->serverState = MasterServer::masterActive;

			//exception area
			acceptor = make_unique<tcp::acceptor>(io_context, tcp::endpoint(tcp::v4(), ftpPort));

			executeMainThread();
			std::cout << "Server is active.\n";
	}
	return true;
}
void MasterServer::stopServer() {
	if (this->serverState != MasterServer::masterStopped) {
			this->acceptor->close();
			this->serverState = MasterServer::masterStopped;
	}
	std::cout << "Server stopped\n";
}


bool MasterServer::insertNewClient( tcp::socket& clientSocket){
	lockMutex();
	try {
			listClients.push_back(make_unique<SlaveServer>(this, clientSocket));
			unlockMutex();
	} catch (std::exception &err) {
		listClients.pop_back();
			unlockMutex();
		cerr << "Unable to add client";
		return false;
	}
	
	return true;
}

void MasterServer::removeSlave(SlaveServer*client) {

	auto iterEnd = listClients.end();
	auto iterBegin = listClients.begin();
	auto iterResult = find_if(iterBegin, iterEnd, [client](unique_ptr<SlaveServer>& uniquePtr) {return uniquePtr.get() == client; });
	if (iterResult != iterEnd) { //If found
		lockMutex();
		listClients.erase(iterResult);
		unlockMutex();
	}

}

void MasterServer::lockMutex() {
	locker.lock();
}
void MasterServer::unlockMutex() {
	locker.unlock();
}

void MasterServer::executeMainThread() {
	threadMasterThread = std::thread{&MasterServer::MasterThread, this};
}

void MasterServer::MasterThread() {
	tcp::socket socket(io_context);

	while (1) {
		try {
				acceptor->accept(socket);
				if (!insertNewClient(socket)) //If failed
						throw std::exception("Memory allocation failed");
				socket.release();
				socket.close();
		}catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
		}
	}
}	


User* MasterServer::findUser(const string& username) {
	auto it = find_if(listUsers.begin(), listUsers.end(), [username](User &user) {return user.isUser(username); });
	if (it != listUsers.end()) {
			return &(*it);
	}		
	else return NULL;
}