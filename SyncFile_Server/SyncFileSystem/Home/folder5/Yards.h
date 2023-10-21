#include <string>

using namespace std;

class Yards
{
private:
	//Data Members
	double yardsVal;
public:
	//Constructors
	Yards();
	Yards(double yardsVal);
	//Setter
	void setYards(double yardsVal);
	//Getter
	double getYards();
	//Nethods For Conversion
	Yards milliToYards(Millimeter mm);
	Yards centiToYards(Centimeter cm);
	Yards meterToYards(Meter m);
	Yards kiloToYards(Kilometer km);
	Yards inchesToYards(Inches i);
	Yards feetToYards(Feet f);
	Yards milesToYards(Miles m);
	Yards nauticalMilesToYards(NauticalMiles nm);
	Yards milsToYards(Mils m);
};