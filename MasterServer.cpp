/*
*																		MasterServer.cpp
*														Master Server class implementation
*
* Author:Amit Herman
*
*/

#include "MasterServer.hpp"
#include <qfile.h>
#include <iostream>
#include <memory>


MasterServer::MasterServer() :maxClients(10), limitClients(true), msgWelcome("FTP Server by Amit Herman"),
error(false) {
	QObject::connect(&MainSocket, &QTcpServer::newConnection, this, &MasterServer::acceptConnection);
}

MasterServer::MasterServer(const QString &pathConfig) {
	error=loadConfig(pathConfig);
	QObject::connect(&MainSocket, &QTcpServer::newConnection, this, &MasterServer::acceptConnection);
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
				usersList.push_back(temp);
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
			if (!MainSocket.listen(QHostAddress::Any, (quint16)ftpPort)) {
				return false;
			}
			std::cout << "Server is active.\n";
	}
	return true;
}
void MasterServer::stopServer() {
	if (this->serverState != MasterServer::masterStopped) {
			MainSocket.close();
	}
	std::cout << "Server stopped\n";
}
/*					Slots				 */
bool MasterServer::acceptConnection() {
	std::cout << "Client connected\n";
	std::unique_ptr<QTcpSocket> nextClient = nullptr;
	nextClient = (std::unique_ptr<QTcpSocket>)MainSocket.nextPendingConnection();
	nextClient->write(msgWelcome.toUtf8());
	return true;
}
