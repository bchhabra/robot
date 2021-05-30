#include <LSM6.h>
#include <LIS3MDL.h>

//LSM6 gyro_acc;
//LIS3MDL mag;
Madgwick filter;
unsigned long microsPerReading, microsPrevious;
float accelScale, gyroScale;

void mag_setup() {
  gyro_acc.init();
//  gyro_acc.enableDefault();
  gyro_acc.writeReg(LSM6::CTRL1_XL, 0x20); // 26 Hz, 2 g full scale
  gyro_acc.writeReg(LSM6::CTRL2_G, 0x20); // 26 Hz, 245 dps full scale
//  gyro_acc.writeReg(LSM6::CTRL1_XL, 0x3C); // 52 Hz, 8 g full scale
//  gyro_acc.writeReg(LSM6::CTRL2_G, 0x4C); // 104 Hz, 2000 dps full scale

  mag.init();
  mag.enableDefault();
  mag.writeReg(LIS3MDL::CTRL_REG1, 0x74); // 20 Hz

  filter.begin(25);

  // initialize variables to pace updates to correct rate
  microsPerReading = 1000000 / 25;
  microsPrevious = micros();
}

void mag_loop(void (*f)()) {
  int aix, aiy, aiz;
  int gix, giy, giz;
  int mix, miy, miz;
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch, yaw;
  unsigned long microsNow;

  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {

  gyro_acc.readAcc();
  aix = gyro_acc.a.x >> 4; // shift left 4 bits to use 12-bit representation (1 g = 256)
  aiy = gyro_acc.a.y >> 4;
  aiz = gyro_acc.a.z >> 4;
  
  gyro_acc.readGyro();
  gix = gyro_acc.g.x;
  giy = gyro_acc.g.y;
  giz = gyro_acc.g.z;
  
  mag.read();
  mix = mag.m.x;
  miy = mag.m.y;
  miz = mag.m.z;

    // convert from raw data to gravity and degrees/second units
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix);
    gy = convertRawGyro(giy);
    gz = convertRawGyro(giz);
    mx = convertRawCompass(mix);
    my = convertRawCompass(miy);
    mz = convertRawCompass(miz);

    // update the filter, which computes orientation
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);
//    filter.updateIMU(gx, gy, gz, ax, ay, az);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    yaw = filter.getYaw();
      Serial.print("!");
      Serial.print("ANG:");
      Serial.print(roll);
      Serial.print(",");
      Serial.print(pitch);
      Serial.print(",");
      Serial.print(yaw);
      Serial.println();
      Serial.println(mx);
      Serial.println(my);
      Serial.println(mz);

    // increment previous time, so we keep proper pace
    microsPrevious = microsPrevious + microsPerReading;
    f();
  }
}

float convertRawAcceleration(int aRaw) {
  float a = aRaw / 61;
  return a;
}

float convertRawGyro(int gRaw) {
  float g = gRaw * 8.75/1000;
  return g;
}

float convertRawCompass(int gRaw) {
  float g = gRaw;// / 6842;
  return g;
}
