#define KILOMETER_H
#ifdef KILOMETER_H

#include <string>

using namespace std;

class Kilometer
{
private:
	//Data Members
	double kiloVal;
public:
	//Constructor
	Kilometer();
	Kilometer(double kiloVal);
	//Setter
	void setKiloVal(double kiloVal);
	//Getter
	double getKiloVal();
	//Methods For Conversion
	Kilometer milliToKilo(Millimeter mm);
	Kilometer centiToKilo(Centimeter cm);
	Kilometer meterToKilo(Meter m);
	Kilometer inchesToKilo(Inches i);
	Kilometer feetToKilo(Feet f);
	Kilometer yardsToKilometer(Yards y);
	Kilometer milesToKilo(Miles m);
	Kilometer nauticalMilesToKilo(NauticalMiles nm);
	Kilometer milsToKilo(Mils m);
	//Methods To Display
	string getKilometer();
	void printKilometer();
};

#endif