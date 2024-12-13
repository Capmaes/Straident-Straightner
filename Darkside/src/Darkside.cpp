#include "Particle.h"  // Include this if you're using the Particle platform, replace with the appropriate include for other platforms
#include "IoTTimer.h"
#include "Grove-Ultrasonic-Ranger.h"
// Define the ultrasonic sensors
Ultrasonic Strident(D3);  // Connect Strident sensor to pin D3
Ultrasonic Ultra(D7);     // Connect Ultra sensor to pin D7

const int Speaker = D15;  // Connect speaker to pin A5

long lastReadingStrident = 0;
long lastReadingUltra = 0;

void setup() {
  Serial.begin(9600);  // Start serial communication
  pinMode(Speaker, OUTPUT);  // Set the speaker pin as output
}

void loop() {
  // Get readings from both ultrasonic sensors
  long stridentReading = Strident.MeasureInInches();
  long ultraReading = Ultra.MeasureInInches();

  // Print the sensor readings for debugging purposes
  Serial.printf("Strident: %ld inches, Ultra: %ld inches\n", stridentReading, ultraReading);

  // Check if the readings don't match
  if (stridentReading != ultraReading) {
    Serial.println("Readings don't match! Triggering sound...");
    tone(Speaker, 440);  // Play a sound on the speaker (frequency 440Hz)
  } else {
    noTone(Speaker);  // Turn off the sound if the readings match
  }

  delay(500);  // Wait for half a second before taking the next reading
}