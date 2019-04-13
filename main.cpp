#include <QtCore/QCoreApplication>
#include <QtCore/qxmlstream.h>
#include "qfile.h"
#include <iostream>
#include "MasterServer.hpp"
#include <csignal>
#include <boost/asio.hpp>



void handlerQuit(int signum) {
	std::cout << "Good bye/n";
	QCoreApplication::quit();
}

int main(int argc, char *argv[])
{
	int out;
	QCoreApplication a(argc, argv);
	MasterServer master;
	master.loadConfig("config.xml");
	signal(SIGINT, handlerQuit);
	master.startServer();
	out = a.exec();
	master.stopServer();
	return out;
}