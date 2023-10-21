#define MILLIMETER_H
#ifdef MILLIMETER_H

#include <string>
#include "Meter.h"
#include "Kilometer.h"
#include "Feet.h"
#include "Inches.h"
#include "Miles.h"
#include "Mils.h"
#include "NauticalMiles.h"
#include "Yards.h"


using namespace std;

class Millimeter
{
private:
	//Data Members
	double milliVal;
public:
	//Constructors
	Millimeter();
	Millimeter(double milliVal);
	//Setter
	void setMilliVal(double milliVal);
	double getMilliVal();
	//Methods For Conversion
	Millimeter centiToMilli(Centimeter cm);
	Millimeter meterToMilli(Meter m);
	Millimeter kiloToMilli(Kilometer km);
	Millimeter inchesToMilli(Inches i);
	Millimeter feetToMilli(Feet f);
	Millimeter yardsToMilli(Yards y);
	Millimeter milesToMilli(Miles m);
	Millimeter nauticalMilesToMilli(NauticalMiles nm);
	Millimeter milsToMilli(Mils m);
	//Methods To Display
	string getMillimeter();
	void printMillimeter();
};

#endif