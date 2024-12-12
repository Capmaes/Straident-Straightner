/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "IoTTimer.h"
#include "Grove-Ultrasonic-Ranger.h"
// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);
SerialLogHandler logHandler(LOG_LEVEL_INFO);
Ultrasonic Strident (D3);
Ultrasonic Ultra (D7);
IoTTimer SoundTimer;

//Variables Ultrasonic & Speaker
int position;
const int Speaker (D15); //PWM pin
bool prevP = false;
long oldPosition = -999;
long RangeinInches;
// Show system, cloud connectivity, and application logs over USB
// View logs with CLI using 'particle serial monitor --follow'


// setup() runs once, when the device is first turned on
void setup() {
 Serial.begin(9600);
waitFor(Serial.isConnected,10000);
pinMode(Speaker,OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  //Ultrasonic Sensor code 
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
	tone(Speaker,440,5000);
   }

	else{
		if(SoundTimer.isTimerReady()){
		noTone(Speaker);
		}
	}
}