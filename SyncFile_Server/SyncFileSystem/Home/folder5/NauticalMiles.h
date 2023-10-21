#include <string>

using namespace std;

class NauticalMiles
{
private:
	//Data Members
	double nautiVal;
public:
	//Constructors
	NauticalMiles();
	NauticalMiles(double nautiVal);
	//Setter
	void setNautiVal(double nautiVal);
	//Getter
	double getNautiVal();
	//Methods For Conversion
	NauticalMiles milliToNauti(Millimeter mm);
	NauticalMiles centiToNauti(Centimeter cm);
	NauticalMiles meterToNauti(Meter m);
	NauticalMiles kiloToNauti(Kilometer km);
	NauticalMiles inchesToNauti(Inches i);
	NauticalMiles feetToNauti(Feet f);
	NauticalMiles yardsToNauti(Yards y);
	NauticalMiles milesToNauti(Miles m);
	NauticalMiles milsToNauti(Mils m);
};