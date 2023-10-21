#include <iostream>
#include "Validations.h"

bool numCheck(char ch)
{
	if (ch >= '0' && ch <= '9')
		return true;
	return false;
}

bool alphaCheck(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return true;
	return false;
}

bool symbolCheck(char ch)
{
	if (!numCheck(ch) && !alphaCheck(ch))
		return true;
	return false;
}

bool userNameCheck(string str)
{
	size_t res = str.find(' ');
	if (!(res == string::npos))
		return false;
	int len = str.length();
	if (len > 20)
		return false;
	if (numCheck(str[0]))
		return false;
	for (int j = 0; j < len; j++)
	{
		if (!(numCheck(str[j]) || alphaCheck(str[j]) || str[j] == '_'))
			return false;
	}
	return true;
		
}

bool passwordCheck(string str)
{
	size_t res = str.find(' ');
	if (!(res == string::npos))
		return false;
	int len = str.length();
	if (len > 20)
		return false;
	return true;
}