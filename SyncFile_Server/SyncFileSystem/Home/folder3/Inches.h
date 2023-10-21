#define INCHES_H
#ifdef INCHES_H

#include <string>
#include "Kilometer.h"
#include "Miles.h"
#include "Milllimeter.h"
#include "MIls.h"
#include "NauticalMiles.h"
#include "Yards.h"

using namespace std;

class Inches
{
private:
	//Data Members
	double inchesVal;
public:
	//Constructors
	Inches();
	Inches(double inchesVal);
	//Setter
	void setInchesVal(double inchesVal);
	double getInchesVal();
	//Mothods For Conversion
	Inches milliToInches(Millimeter mm);
	Inches centiToInches(Centimeter cm);
	Inches meterToInches(Meter m);
	Inches kiloToInches(Kilometer km);
	Inches feetToInches(Feet f);
	Inches yardsToInches(Yards y);
	Inches milesToInches(Miles m);
	Inches nauticalMilesToInches(NauticalMiles nm);
	Inches milsToInches(Mils m);
	//Methods To Display
	string getInches();
	void printInches();
};

#endif