#pragma once

#include <Wire.h>
#include "imu/Imu.h"
#include <imu/I2C.h>
#include <imu/Compass.h>
#include <imu/DCM.h>
#include "imu/matrix.h"
#include "imu/Vector.h"
#include "imu/Output.h"

int initialDeg;

namespace Imu {

long timer=0;   //general purpuse timer
long timer_old;
long timer24=0; //Second timer used to print values

unsigned int counter=0;
byte gyro_sat=0;

int readAngle();

void setup()
{
#if IMU

	I2C_Init();

  // pinMode (STATUS_LED,OUTPUT);  // Status LED

  // digitalWrite(STATUS_LED,LOW);
  delay(1500);

  Accel_Init();
  Compass_Init();
  Gyro_Init();

  delay(20);

  for(int i=0;i<32;i++)    // We take some readings...
    {
    Read_Gyro();
    Read_Accel();
    for(int y=0; y<6; y++)   // Cumulate values
      AN_OFFSET[y] += AN[y];
    delay(20);
    }

  for(int y=0; y<6; y++)
    AN_OFFSET[y] = AN_OFFSET[y]/32;

  AN_OFFSET[5]-=GRAVITY*SENSOR_SIGN[5];

  //Serial.println("Offset:");
  // for(int y=0; y<6; y++)
  //   Serial.println(AN_OFFSET[y]);

  delay(2000);
  // digitalWrite(STATUS_LED,HIGH);

  timer=millis();
  delay(20);
  counter=0;

	initialDeg = readAngle();

#endif
}

void loop() //Main Loop
{
#if IMU

  if((millis()-timer)>=20)  // Main loop runs at 50Hz
  {
    counter++;
    timer_old = timer;
    timer=millis();
    if (timer>timer_old)
    {
      G_Dt = (timer-timer_old)/1000.0;    // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
      if (G_Dt > 0.2)
        G_Dt = 0; // ignore integration times over 200 ms
    }
    else
      G_Dt = 0;



    // *** DCM algorithm
    // Data adquisition
    Read_Gyro();   // This read gyro data
    Read_Accel();     // Read I2C accelerometer

    if (counter > 5)  // Read compass data at 10Hz... (5 loop runs)
    {
      counter=0;
      Read_Compass();    // Read I2C magnetometer
      Compass_Heading(); // Calculate magnetic heading
    }

    // Calculations...
    Matrix_update();
    Normalize();
    Drift_correction();
    Euler_angles();
    // ***

    printdata();
  }

#endif
}

inline int readAngle() {
  return ToDeg(yaw);
}

inline int calculateDelta(int currentDeg, int originalDeg) {
	int signedAngle = ((currentDeg - originalDeg) + 180) % 360 - 180;
	return abs(signedAngle);
}

}
