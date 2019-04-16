/*
																									ftpcmds.hpp
																							FTP Commands headers
*/
#ifndef _FTPCOMMANDS_H
#define _FTPCOMMANDS_H
#include <string>
#include <vector>
 
using namespace std;
namespace FTP {

	/*
	/				Username
	/	Format: USER <username>
	/	Reply Codes:
	/		230 User logged in
	/		530 Username not found
	/		501 Syntax Error
	/		331 Enter password
	/
	/**/
	static const string cmdUSER = "USER";


	/*
	/				password
	/	Format: PASS <password>
	/	Reply codes:
	/		230 logged in
	/		530 Password incorrect
	/   503 Enter username first
	/		501 Syntax error
	/*/
	static const string cmdPASS = "PASS";

	/*
	/				noop
	/	Format: NOOP
	/	Reply codes:
	/		200 OK
			501 syntax error
	/*/
	static const string cmdNOOP = "NOOP";


	/*
	/				MODE
	/	Format: MODE (s)
	/	Reply codes:
	/		200 OK
			501 syntax error
	/*/
	static const string cmdMODE = "MODE";


	/*
	/				Structure
	/	Format: STRU (F)
	/	Reply codes:
	/		200 OK
			501 syntax error
	/*/
	static const string cmdSTRU = "STRU";

	/*
	/				Reinitialize
	/	Format: REIN
	/	Reply codes:
	/		120 logged out, Waiting for Data transfer to be completed.
	/		220 Logged out
	/
	/*/
	static const string cmdREIN = "REIN";



	/*
	/				Print Working Directory
	/	Format: PWD
	/	Reply codes:
	/		530 Not logged in
	/		257 <pathname>
	/
	/*/
	static const string cmdPWD = "PWD";

	/*
/				Change Working Directory
/	Format: PWD
/	Reply codes:
/		250 Okay(Found and changed)
/		550 Directory not found
/
/*/
	static const string cmdCWD = "CWD";



	/*
/				Change Directory Up
/	Format: CDUP
/	Reply codes:
/		200 Okay(Found and changed)
/		550 Directory not found
/
/*/
	static const string cmdCDUP = "CDUP";

	/*
/				Passive mode
/	Format: PASV
/	Reply codes:
/		227 h1,h2,h3,h4,p1,p2
/
/*/
	static const string cmdPASV = "PASV";


	/*
/				Port(Active mode
/	Format: PORT h1,h2,h3,h4,p1,p2
/	Reply codes:
/		227 h1,h2,h3,h4,p1,p2
/
/*/
	static const string cmdPORT = "PORT";

}
#endif