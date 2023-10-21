#include <iostream>
#include <conio.h>
#include "Units.h"

using namespace std;

int main()
{
	cout << "Hello World" << endl;
	
	Millimeter mm1(5);
	Centimeter cm1;
	cm1.milliToCenti(mm1);
	cm1.printCentimeter();

	_getch();
	return 0;
}