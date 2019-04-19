/*
/																								QDirExtended.hpp
/															QDir with option for base path as a root dir.(headers)
/
*/

#ifndef _QDIREXTENDED_HPP
#define _QDIREXTENDED_HPP
#include <QDir>
#include <string>
using namespace std;

class QDirExtended  {
private:
	QDir baseDir;
	QDir currentDir;
public:
	QDirExtended() = default;
	QDirExtended(const QString &path);
	~QDirExtended() = default;

	bool cd(const QString &dirName);
	void setBasePath(const QString &path);
	void setCurrentPath(const QString &path);
	void setCurrentPath();
	void cdup();
	bool exists(const QString &relativePath);
	bool exists();
	string relativePath();
	QStringList entrylist();
};

#endif