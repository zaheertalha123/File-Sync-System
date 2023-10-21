#include <iostream>
#include "Units.h"

using namespace std;

//Implementation Of Constructors Of Class "CentiMeter"
Centimeter::Centimeter()
{
	this->centiVal = 0;
}
Centimeter::Centimeter(double centiVal)
{
	this->centiVal = centiVal;
}

//Implementation Of Setters Of Class "CentiMeter"
void Centimeter::setCentiVal(double centiVal)
{
	this->centiVal = centiVal;
}

//Implementation Of Getters Of Class "CentiMeter"
double Centimeter::getCentiVal()
{
	return this->centiVal;
}

//Implementation Of Methods For Conversion Of Class "CentiMeter"
Centimeter Centimeter::milliToCenti(Millimeter mm)
{
	return Centimeter(mm.getMilliVal() / 10);
}
Centimeter meterToCenti(Meter m);
Centimeter kiloToCenti(Kilometer km);
Centimeter ichesToCenti(Inches i);
Centimeter feetToCenti(Feet f);
Centimeter yardsToCenti(Yards y);
Centimeter milesToCenti(Miles m);
Centimeter nauticalMilesToCenti(NauticalMiles nm);
Centimeter milsToCenti(Mils m);

//Implementation Of Methods To Display Class "CentiMeter"
string Centimeter::getCentimeter()
{
	return to_string(this->getCentiVal()) + " cm";
}
void Centimeter::printCentimeter()
{
	cout << this->getCentiVal << " cm";
}