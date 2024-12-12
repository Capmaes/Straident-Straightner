/* 
 * Project MP3 Player Test
 * Author: Brian Rashap
 * Date: 10-APR-2024
 */

#include "Particle.h"
// #include "DFRobotDFPlayerMini.h"
#include "IoTTimer.h"

// DFRobotDFPlayerMini Speaker;
  IoTTimer test;

void setup()
{
  pinMode(A2,OUTPUT);

}

void loop()
{

  tone(A2,440);


}

