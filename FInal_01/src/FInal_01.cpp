/* 
 * Project : Strident Straightner 
 * Author: Caprice Harwood
 * Date: December of 2024
 */


#include "Particle.h"
#include "Grove-Ultrasonic-Ranger.h"
#include "IoTTimer.h"

SYSTEM_MODE(SEMI_AUTOMATIC);
SerialLogHandler logHandler(LOG_LEVEL_INFO);
Ultrasonic Strident (D3);
Ultrasonic Ultra (D7);
class IoTTimer SoundTimer;
float position;
const int Speaker (A5);
bool prevP;


void setup()
{
Serial.begin(9600);
waitFor(Serial.isConnected,10000);
pinMode(Speaker,OUTPUT);

}
void loop()
{
	long RangeInInches;
	// long RangeInCentimeters;

	RangeInInches = Strident.MeasureInInches();//set to inches
  if(RangeInInches= !position){
  	Serial.printf("Ultrasonic#:%i\n",RangeInInches);
    prevP=RangeInInches; //if equal don't print
	delay(5000);
   } 
	RangeInInches = Ultra.MeasureInInches();
     if(RangeInInches!=prevP){
  	Serial.printf("Ultrasonic#seccond : %i\n",RangeInInches);
    prevP=RangeInInches; //if equal don't print
	delay(5000);
   } 

	if(Strident!=Ultra){  //if they are not equal sound alarm 
		SoundTimer.start
		tone(Speaker,440);
	}
	else{
		if(SoundTimer,isTimerReady());
		toneOff();
	}
}
	// RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  // Serial.printf("%i \n", RangeInCentimeters);
	// delay(250);



