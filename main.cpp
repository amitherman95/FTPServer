#include <QtCore/QCoreApplication>
#include <QtCore/qxmlstream.h>
#include "qfile.h"
#include <iostream>
#include "MasterServer.h"
#include <csignal>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	MasterServer master;
	master.loadConfig("config.xml");
	signal(SIGINT, handlerQuit);
	return a.exec;
}


void handlerQuit(int signum) {
	QCoreApplication::quit();
}