#include "FileSystem.h"

using namespace std;

//Implementing Private Methods
unsigned long int FileSystem::keyGen(string str)
{
	unsigned long int key = 0;
	for (int j = 0; j < str.length(); j++)
	{
		key += str[j];
	}
	return key;
}

//Implementing Constructors
FileSystem::FileSystem()
{
	this->fileNameWE = "";
	this->fileName = "";
	strcpy(this->extension, "NIL");
	this->fullPath = "";
	this->pathKey = 0;
	this->nameKey = 0;
}
FileSystem::FileSystem(string fileName, string fullPath)
{
	//Setting File Name
	for (int j = 0; j < fileName.length(); j++)
		fileName[j] = tolower(fileName[j]);
	this->fileNameWE = fileName;
	//Setting File Name Without Extension
	string temp = "";
	int len = (int)fileName.length() - 4;
	for (int j = 0; j < len; j++)
		temp += fileNameWE[j];
	this->fileName = temp;
	temp = "";
	//Setting Extension Of File
	for (int j = len+1; j < len+4; j++)
		temp += fileNameWE[j];
	strcpy(this->extension, temp.c_str());
	//Setting Full Path
	this->fullPath = fullPath;
	//Generating Keys
	this->pathKey = keyGen(fullPath);
	this->nameKey = keyGen(this->fileNameWE);
	/*cout << "---------------------------" << endl
		<< "Name : " << fileName << endl
		<< "Path : " << fullPath << endl
		<< "Extension : " << extension << endl
		<< "Name Key : " << nameKey << endl
		<< "Path Key : " << pathKey << endl
		<< "---------------------------" << endl;*/
}
FileSystem::FileSystem(dirent* entity, string fullPath)
{
	string temp = "";
	//Setting File Name
	this->fileNameWE = entity->d_name;
	for (int j = 0; j < fileNameWE.length(); j++)
		fileNameWE[j] = tolower(fileNameWE[j]);
	//Setting Directory/File Name Without Extension
	if (entity->d_type == DT_DIR)
	{
		this->fileName = entity->d_name;
		for (int j = 0; j < fileName.length(); j++)
			fileName[j] = tolower(fileName[j]);
		strcpy(this->extension, "DIR");
	}
	else
	{
		int len = (int)fileNameWE.length() - 4;
		for (int j = 0; j < len; j++)
			temp += fileNameWE[j];
		this->fileName = temp;
		temp = "";
		//Setting Extension Of File
		for (int j = len + 1; j < len + 4; j++)
			temp += fileNameWE[j];
		strcpy(this->extension, temp.c_str());
	}
	//Setting Full Path
	this->fullPath = fullPath;
	//Generating Keys
	this->pathKey = keyGen(fullPath);
	this->nameKey = keyGen(this->fileName);

	//cout << "---------------------------" << endl
	//	<< "Name : " << fileName << endl
	//	<< "Path : " << fullPath << endl
	//	<< "Extension : " << extension << endl
	//	<< "Name Key : " << nameKey << endl
	//	<< "Path Key : " << pathKey << endl
	//	<< "---------------------------" << endl;
}

//Implementing Destructor
FileSystem::~FileSystem()
{}

//Implementing Setters
void FileSystem::setPathKey()
{
	this->pathKey = keyGen(fullPath);
}
void FileSystem::setNameKey()
{
	this->nameKey = keyGen(this->fileNameWE);
}
void FileSystem::setFileNameWE(string fileNameWE)
{
	this->fileNameWE = fileNameWE;
}
void FileSystem::setFileName(string fileName)
{
	this->fileName = fileName;
}
void FileSystem::setExtension(char* extension)
{
	strcpy(this->extension, extension);
}
void FileSystem::setFullPath(string fullPath)
{
	this->fullPath = fullPath;
}

//Implementing Getters
unsigned long int FileSystem::getPathKey()
{
	return this->pathKey;
}
unsigned long int FileSystem::getNameKey()
{
	return this->nameKey;
}
string FileSystem::getFileNameWE()
{
	return this->fileNameWE;
}
string FileSystem::getFileName()
{
	return this->fileName;
}
string FileSystem::getExtension()
{
	string str = "";
	for (int j = 0; j < 3; j++)
		str += extension[j];
	return str;
}
string FileSystem::getFullPath()
{
	return this->fullPath;
}

//Implementing Other Methods
void FileSystem::printDetails()
{
	cout << "File Name : " << this->fileName << "\n"
		<< "Type/Extension : " << this->extension[0] << this->extension[1] << this->extension[2] << "\n"
		<< "Full Path : " << this->fullPath << "\n"
		<< "Full Path Key : " << this->pathKey << "\n"
		<< "Name Key : " << this->nameKey << endl;
}
string FileSystem::getDetails()
{
	return "File Name : " + this->fileName + "\n"
		+ "Type/Extension : " + this->extension[0] + this->extension[1] + this->extension[2] + "\n"
		+ "Full Path : " + this->fullPath + "\n"
		+ "Full Path Key : " + to_string(this->pathKey) + "\n"
		+ "Name Key : " + to_string(this->nameKey) + "\n";
}
string FileSystem::getValidLocation()
{
	if (fullPath == "")
		return "";
	string str = "";
	int j;
	int len1;
	for (j = 0, len1 = 0; j < fullPath.length(); j++, len1++)
	{
		if (fullPath[j] == 'H' || fullPath[j] == 'H')
		{
			if (fullPath[j + 4] == '\\' || j + 4 == fullPath.length())
				break;
		}
	}
	len1 = fullPath.length() - len1;
	return fullPath.substr(j, len1);
}
