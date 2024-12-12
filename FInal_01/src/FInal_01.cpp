/* 
 * Project : Strident Straightner 
 * Author: Caprice Harwood
 * Date: December of 2024
 */


#include "Particle.h"
#include "Grove-Ultrasonic-Ranger.h"
#include "IoTTimer.h"

//MQQTT Libaries 
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "credentials.h"

TCPClient TheClient; 
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 
// MQTT paths for AIO form: <username>/feeds/<feedname> 
Adafruit_MQTT_Subscribe ButFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/Score/buttononoff"); 
Adafruit_MQTT_Publish ScoreFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/buttononoff/Score");
SYSTEM_MODE(SEMI_AUTOMATIC);
//Class
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

//Functions and Variables for MQTT
void MQTT_connect();
bool MQTT_ping();
unsigned int last, lastTime;
float ButValue,ScoreValue;
bool ButtonState;
int random , Score;




void setup(){
Serial.begin(9600);
waitFor(Serial.isConnected,10000);
pinMode(Speaker,OUTPUT);

WiFi.on();
WiFi.connect();
while(WiFi.connecting()) {
Serial.printf("is connecting");
	}
  mqtt.subscribe(&ButFeed);
}



void loop() {
  MQTT_connect();
  MQTT_ping();

  // this is our 'wait for incoming subscription packets' busy subloop 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(100))) {
    if (subscription == &ButFeed) {
      ButValue = atoi((char *)ButFeed.lastread);
pinMode(Speaker,OUTPUT);
Ultrasonic Strident (D3);
Ultrasonic Ultra (D7);
    }
  }

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
	
	if((millis()-lastTime > 6000)) {
    if(mqtt.Update()) {
      ScoreValue = RangeInInches;
    if(ScoreValue=!lastTime){ 
       Serial.printf("Score: %0.2f\n",ScoreValue);
      } 
    ScoreFeed.publish(ScoreValue);
    Serial.printf("Publishing %0.2f\n",ScoreFeed);  

    lastTime = millis();
    }
  }
}





	// Function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {
  int8_t ret;
 	 // Return if already connected.
  if (mqtt.connected()) {
    return;
  }
Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.printf("Error Code %s\n",mqtt.connectErrorString(ret));
       Serial.printf("Retrying MQTT connection in 5 seconds...\n");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds and try again
  }
  Serial.printf("MQTT Connected!\n");
}

bool MQTT_ping() {
  static unsigned int last;
  bool pingStatus;

  if ((millis()-last)>6000) {
      Serial.printf("Pinging MQTT \n");
      pingStatus = mqtt.ping();
      if(!pingStatus) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      last = millis();
  }
  return pingStatus;
}

