#ifndef FILESYSTEM
#define FILESYSTEM

#include <string>
#include <iostream>
#include <cctype>
#include "Dirent.h"

using namespace std;

class FileSystem
{
private:
	//Data Members
	unsigned long int pathKey;
	unsigned long int nameKey;
	string fileNameWE;
	string fileName;
	char extension[3];
	string fullPath;
	//Private Methods
	unsigned long int keyGen(string str);
public:
	//Constructor
	FileSystem();
	FileSystem(string fileName, string fullPath);
	FileSystem(dirent* entity, string fullPath);
	//Destructor
	~FileSystem();
	//Setters
	void setPathKey();
	void setNameKey();
	void setFileNameWE(string fileNameWE);
	void setFileName(string fileName);
	void setExtension(char* extension);
	void setFullPath(string fullPath);
	//Getters
	unsigned long int getPathKey();
	unsigned long int getNameKey();
	string getFileNameWE();
	string getFileName();
	string getExtension();
	string getFullPath();
	//Other Methods
	void printDetails();
	string getDetails();
	string getValidLocation();
};

#endif