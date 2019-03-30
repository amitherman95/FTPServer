/*
*																	User.h
*														User class header
*
* Author:Amit Herman
*
*	Description:each client has to log in to some account in order to use the server
*							MasterServer has list of users which the client can pick.
*/

#ifndef USER_H
#define USER_H

#include <QtCore>
/**
\class Hold data about users and what access permissions they have in the server
The class should be compatible with Standard Library containers
*/
class User {
private:
	QString username;
	QString password;
	QString rootdir;
	bool canRead;
	bool canWrite;
	bool canDelFiles;
	bool canManipulateDirs; //*<Permission to do all sort of stuff to directories delete rename...

public:
	/** default constructor*/
	User();
	/**Copy Constructor */
	User(const User& src);
	/**Move constructor*/
	User(User&& src) noexcept;
	/**Move Assignment operator overload*/
	User &operator=(User&& rhs) noexcept;
	/**Regular assignment operator overload*/
	User operator=(const User& rhs);


	/**Comparison opeator overload*/
	bool operator==(const User& rhs);
	/**Check whether the pass is right*/
	bool isPassRight(const QString& pass);

	/**Yet another constructor*/
	User(const QString& username, const QString& password, bool read = false,
		bool write = false, bool delFiles = false, bool manipulateDirs = false);

	/**\returnReturns true if the username matches to the parameter
	* \param Username string to compare with the object member.
	*/
	bool isUser(const QString &userName);

	void setPass(const QString &pass);
	void setUsername(const QString &user);
	void setRootDir(const QString &rootDir);
	void setRead(bool read);
	void setWrite(bool write);
	void setDel(bool del);
	void setManDir(bool manDir);
	QString getRootDir();
	bool getCanRead();
	bool getCanWrite();
	bool getCanDel();
	bool getCanManDir();
};
#endif
