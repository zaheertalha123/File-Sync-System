#define CENTIMETER_H
#ifdef CENTIMETER_H

#include <string>
#include "Feet.h"
#include "Milllimeter.h"
#include "Meter.h"
#include "Kilometer.h"
#include "Inches.h"
#include "Feet.h"
#include "Yards.h"
#include "Miles.h"
#include "NauticalMiles.h"
#include "Miles.h"

using namespace std;

class Centimeter
{
private:
	//Data Members
	double centiVal;
public:
	//Constructors
	Centimeter();
	Centimeter(double centiVal);
	//Setter
	void setCentiVal(double centiVal);
	//Getters
	double getCentiVal();
	//Methods For Conversion
	Centimeter milliToCenti(Millimeter mm);
	Centimeter meterToCenti(Meter m);
	Centimeter kiloToCenti(Kilometer km);
	Centimeter ichesToCenti(Inches i);
	Centimeter feetToCenti(Feet f);
	Centimeter yardsToCenti(Yards y);
	Centimeter milesToCenti(Miles m);
	Centimeter nauticalMilesToCenti(NauticalMiles nm);
	Centimeter milsToCenti(Mils m);
	//Methods To Display
	string getCentimeter();
	void printCentimeter();
};

#endif