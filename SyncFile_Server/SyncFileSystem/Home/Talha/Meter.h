#define METER_H
#ifdef METER_H

#include <string>
#include "Inches.h"
#include "Kilometer.h"
#include "Miles.h"
#include "Milllimeter.h"
#include "Mils.h"
#include "NauticalMiles.h"
#include "Yards.h"

using namespace std;

class Meter
{
private:
	//Data Members
	double meterVal;
public:
	//Constructors
	Meter();
	Meter(double meterVal);
	//Setter
	void setMeterVal(double meterVal);
	double getMeterVal();
	//Methods For Conversion
	Meter milliToMeter(Millimeter mm);
	Meter centiToMeter(Centimeter cm);
	Meter kiloToMeter(Kilometer km);
	Meter inchesToMeter(Inches i);
	Meter feetToNeter(Feet f);
	Meter yardsToMeter(Yards y);
	Meter milesToMeter(Miles m);
	Meter nauticalMilesToMeter(NauticalMiles);
	Meter milsToMeter(Mils m);
	//Methods To Display
	string getMeter();
	void printMeter();
};

#endif