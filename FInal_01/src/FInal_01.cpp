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
// // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 
// MQTT paths for AIO form: <username>/feeds/<feedname> 
Adafruit_MQTT_Publish u_ultrasonicFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/upperultrasonic"); 
Adafruit_MQTT_Publish l_ultrasonicFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/lowerultrasonic");
SYSTEM_MODE(SEMI_AUTOMATIC);
//Class
Ultrasonic Strident (D3);
Ultrasonic Ultra (D7);
IoTTimer SoundTimer;

//Variables Ultrasonic & Speaker
long upperRangeInInches;
long lowerRangeInInches;
unsigned int lastPublish;
//Variables Ultrasonic & Speaker
int position;
const int Speaker (D15); //PWM pin
bool prevP = false;
long oldPosition = -999;
long RangeinInches;

// //Functions and Variables for MQTT
void MQTT_connect();
bool MQTT_ping();




void setup(){
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  pinMode(Speaker,OUTPUT);

  WiFi.on();
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf("is connecting");
  }

}


void loop() {
  MQTT_connect();
  MQTT_ping();

  //Ultrasonic Sensor code for MQTT
upperRangeInInches = Ultra.MeasureInInches();//Measure in inches
lowerRangeInInches = Strident.MeasureInInches();

  if(upperRangeInInches <= 10 && lowerRangeInInches <= 10){ // If someone is sitting in the chair
    if((millis() - lastPublish) > 3000){ // Start a timer that will publish every 3 seconds
      lastPublish = millis();
      if(mqtt.Update()){ // If there is still a connection with the mqtt broker
        u_ultrasonicFeed.publish(upperRangeInInches); // publish
        l_ultrasonicFeed.publish(lowerRangeInInches); // publish
        Serial.printf("Upper Ultrasonic: %i ---- Lower Ultrasonic: %i \n",upperRangeInInches, lowerRangeInInches);
      }
    }
  }

upperRangeInInches = Ultra.MeasureInInches();//Measure in inches
lowerRangeInInches = Strident.MeasureInInches();
   if( lowerRangeInInches && upperRangeInInches => 8){
	//if upper&lower sensor more than 8 then sound alarm for bad posture 
	SoundTimer.startTimer(5000);
	tone(Speaker,440,5000);
   }

	else{
		if( Ultra.MeasureInInches() && Strident.MeasureInInches() =< 8){
			//if sensor readings are less than 8 no alarm.
		SoundTimer.isTimerReady()
		noTone(Speaker);
		}
	}

}





// 	// Function to connect and reconnect as necessary to the MQTT server.
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