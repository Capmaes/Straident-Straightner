/* 
 * Project : Final
 * Author: Caprice Harwood
 * Date: December 2024
 */


#include "Particle.h"
// #include "DFRobotDFPlayerMini.h"
#include "Grove-Ultrasonic-Ranger.h"
SYSTEM_MODE(SEMI_AUTOMATIC);
SerialLogHandler logHandler(LOG_LEVEL_INFO);
Ultrasonic Strident (D3);
Ultrasonic Ultra (D7);
// int position,prevpos;

 

void setup()
{
Serial.begin(9600);
waitFor(Serial.isConnected,10000);

}
void loop()
{
	long RangeInInches;
	long RangeInCentimeters;

	RangeInInches = Strident.MeasureInInches();
	RangeInCentimeters = Ultra.MeasureInCentimeters();
	// if(position!=prevpos){
	Serial.printf("Ultrasonic#1 %i\n",RangeInInches);
	delay(250);
	Serial.printf("Ultrasonic#2 %i\n",RangeInCentimeters);
	// prevpos=position;
	}
	// RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  // Serial.printf("%i \n", RangeInCentimeters);
	// delay(250);
