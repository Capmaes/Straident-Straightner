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
IoTTimer SoundTimer;
int position;
const int Speaker (A5);
bool prevP = false;
long oldPosition = -999;
long RangeinInches;

void setup()
{
Serial.begin(9600);
waitFor(Serial.isConnected,10000);
pinMode(Speaker,OUTPUT);

}
void loop()
{
	long RangeInInches;
	RangeInInches = Strident.MeasureInInches();//set to inches
  
  	if(RangeInInches!= position){
  	Serial.printf("Ultrasonic#: %i \n",RangeInInches);
    position=RangeInInches; //if equal don't print
	delay(5000);
   } 
	RangeInInches = Ultra.MeasureInInches();
     if(RangeInInches!=prevP){
  	Serial.printf("Ultrasonic#seccond : %i\n",RangeInInches);
    prevP=RangeInInches; //if equal don't print
	delay(5000);
   } 


   if(position != Ultra.MeasureInInches() && position != Strident.MeasureInInches()){
	oldPosition = position;
	SoundTimer.startTimer(5000);
	tone(Speaker,440);
   }

	else{
		if(SoundTimer.isTimerReady()){
		noTone(Speaker);
		}
	
	}
}


//foundout encoder.read( ) is the same as ultra.measure 6pm
// long oldPosition  = -999;

// void loop() {
//   long newPosition = myEnc.read();
//   if (newPosition != oldPosition) {
//     oldPosition = newPosition;
//     Serial.println(newPosition);
//   }
// && to check two statements are true }
//get it to ignore numbers above 15 if above 5 posture bad