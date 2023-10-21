#define MILES_H
#ifdef MILES_H

#include <string>
#include "Feet.h"
#include "Inches.h"
#include "Kilometer.h"
#include "Meter.h"
#include "Milllimeter.h"
#include "Mils.h"
#include "NauticalMiles.h"
#include "Yards.h"

using namespace std;

class Miles
{
private:
	//Data Members
	double milesVal;
public:
	//Constructors
	Miles();
	Miles(double milesVal);
	//Setter
	void setMilesVal(double milesVal);
	//Getter
	double getMilesVal();
	//Methods For Conversion
	Miles milliToMiles(Millimeter mm);
	Miles centiToMiles(Centimeter cm);
	Miles meterToMiles(Meter m);
	Miles kiloToMiles(Kilometer km);
	Miles inchesToMiles(Inches i);
	Miles feetToMiles(Feet f);
	Miles yardsToMiles(Yards y);
	Miles nauticalMilesToMiles(NauticalMiles nm);
	Miles milsToMiles(Mils m);
	//Methods To Display
	string getMiles();
	void printMiles();
};

#endif