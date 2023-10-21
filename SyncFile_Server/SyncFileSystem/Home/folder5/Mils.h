#include <string>

using namespace std;

class Mils
{
private:
	//Data Members
	double milsVal;
public:
	//Constructors
	Mils();
	Mils(double milsVal);
	//Setter
	void setMilsVal(double milsVal);
	//Getter
	double getMilsVal();
	//Methods For Conversion
	Mils milliToMils(Millimeter mm);
	Mils centiToMils(Centimeter cm);
	Mils meterToMils(Meter m);
	Mils kiloToMils(Kilometer km);
	Mils inchesToMils(Inches i);
	Mils feetToMils(Feet f);
	Mils yardsToMils(Yards y);
	Mils milesToMils(Miles m);
	Mils nauticalMilesToMils(NauticalMiles nm);
	//Methods To Display
	string getMils();
	void printMils();
};