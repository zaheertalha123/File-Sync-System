#define FEET_H
#ifdef FEET_H

#include <string>
#include "Milllimeter.h"
#include "Meter.h"
#include "Kilometer.h"
#include "Inches.h"
#include "Yards.h"
#include "Miles.h"
#include "NauticalMiles.h"
#include "Mils.h"

using namespace std;

class Feet
{
private:
	//Data Memvbers
	double feetVal;
public:
	//Constructors
	Feet();
	Feet(double feetVal);
	//Setter
	void setFeetVal(double feetVal);
	//Getter
	double getFeetVal();
	//Methods For Conversion
	Feet milliToFeet(Millimeter mm);
	Feet centiToFeet(Centimeter cm);
	Feet meterToFeet(Meter m);
	Feet kiloToFeet(Kilometer km);
	Feet inchesToFeet(Inches i);
	Feet yardsToFeet(Yards y);
	Feet milesToFeet(Miles m);
	Feet nauticalMilesToFeet(NauticalMiles nm);
	Feet milsToFeet(Mils m);
	//Methods To Display
	string getFeet();
	void printFeet();
};

#endif