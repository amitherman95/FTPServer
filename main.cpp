#include <QtCore/QCoreApplication>
#include <QtCore/qxmlstream.h>
#include "qfile.h"
#include <iostream>
#include "MasterServer.h"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	MasterServer master;
	master.loadConfig("config.xml");


	a.quit();
	return 0;
}



	