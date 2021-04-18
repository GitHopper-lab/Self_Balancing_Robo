/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/
#include <AFMotor.h>
#include <Wire.h>
#include <MPU6050.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

MPU6050 mpu;

int pitch, roll;

void setup()
{
  Serial.begin(9600);

  Serial.println("Initialize MPU6050");

  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor2.setSpeed(200);
  motor2.run(RELEASE);

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{
  scan_gyro();

  if (roll > 0) {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
  }

  if (roll < 0) {
    
    motor1.run(FORWARD);
    motor2.run(FORWARD);

  }

  show_data();
}






void scan_gyro() {

  // Read normalized values
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;

  // Output


}

void show_data() {
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);

  Serial.println();
}
