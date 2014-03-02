#include <ZumoMotors.h>
#include <SoftwareSerial.h>


SoftwareSerial BT(5, 4); // RX, TX

byte in;
int time = 100;
ZumoMotors motors;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
}

void loop() // run over and over
{
  if (BT.available())
    {
        in = BT.read();

        if(in == 76) //Left
        {
          motors.setLeftSpeed(-400);
          motors.setRightSpeed(400);
          delay(time);
          motors.setLeftSpeed(0);
          motors.setRightSpeed(0);
        }

        if(in == 70) //Forward
        {
          motors.setLeftSpeed(400);
          motors.setRightSpeed(400);
        }

        if(in == 82) //Right
        {
          motors.setLeftSpeed(400);
          motors.setRightSpeed(-400);
          delay(time);
          motors.setLeftSpeed(0);
          motors.setRightSpeed(0);
        }

        if(in == 66) //Back
        {
          motors.setLeftSpeed(-400);
          motors.setRightSpeed(-400);
        }
        
        if(in == 83) //Back
        {
          motors.setLeftSpeed(0);
          motors.setRightSpeed(0);
        }
        
      }
}





