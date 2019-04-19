#include "QDirExtended.hpp"

bool QDirExtended::cd(const QString &dirName) {
	QString temp_path = currentDir.path();
	auto list = dirName.split("/");
	for (auto iter = list.begin(); iter != list.end(); ++iter) {
		if (currentDir.cd(*iter)){
				if (!currentDir.relativeFilePath(baseDir.path()).contains("..")) {
						temp_path = currentDir.path();
				}else {
						currentDir.setPath(temp_path);
				}
		}else {
				return false;
		}
	}
	return true;
}


QDirExtended::QDirExtended(const QString &path) {
	baseDir.setPath(path);
	currentDir.setPath(path);
}


void QDirExtended::setBasePath(const QString &path) {
	baseDir.setPath(path);
	currentDir.setPath(path);
}

void QDirExtended::setCurrentPath(const QString &path) {
	currentDir.setPath(path);
}

void QDirExtended::setCurrentPath() {
	currentDir = baseDir;
}
void QDirExtended::cdup() {
	if (baseDir != currentDir) {
			currentDir.cdUp();
	}
}

bool QDirExtended::exists(const QString &relativePath) {

	return currentDir.exists(relativePath);
}

bool QDirExtended::exists() {

	return currentDir.exists();
}

string QDirExtended::relativePath() {
	if (baseDir == currentDir) {
		return "/";
	}
	return "/" + currentDir.relativeFilePath(baseDir.path()).toStdString();
}


QStringList QDirExtended::entrylist() {
	return currentDir.entryList();
}