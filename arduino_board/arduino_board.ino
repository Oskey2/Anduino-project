
#include <Wire.h>
#include <MPU6050.h>

// initializing variables
int pitch;
int roll;
int button = 2; // Toggle button at pin 19
bool pressed = false;

MPU6050 mpu; // Creating an MPU6050(GY521) Object

void buttonToggle()
{
  pressed = true;
}
void setup()
{
  Serial.begin(9600);

  // Serial.println("Initialize MPU6050");

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) // Checking if Accelerometer is connected
  {
    //  Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  pinMode(button, INPUT_PULLUP); // initializing Toggle button as Input
  attachInterrupt(digitalPinToInterrupt(button), buttonToggle, FALLING); // Interrupt to change the display to Roll or Pitch (if Button=LOW)
  delay(1000);
  Serial.flush();
}

void loop()
{
  getAccData();         // Function to get real time data from Accelerometer

  //  Serial.println("X: ");
  //   Serial.print(pitch);
  //Serial.println();
  //Serial.println("Y: ");
  //   Serial.print(roll);
  if (pressed == true)
  {
    pressed = false;
    Serial.write('1');
  }
  if (roll > 60)
  {
    Serial.write('2');
  }
  else if (roll < -60)
  {
    Serial.write('3');
  }

  if (pitch > 60)
  {
    Serial.write('4');
  }
  else if (pitch < -60)
  {
    Serial.write('5');
  }
}

void getAccData()
{
  // Read normalized values
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;

}
