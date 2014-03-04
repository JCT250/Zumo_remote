// Code to control Pololu Zumo from Android 
// phone using accelerometer values


#include <ZumoMotors.h>
#include <SoftwareSerial.h>


SoftwareSerial BT(5, 4); // RX, TX

char in;

int xdir = 0;
int xval = 0;
float xvalmapped = 0;

int ydir = 0;
int yval = 0;
float yvalmapped = 0;

char data[11] = {
  'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'};

int scale = 30; //adjust to configure the ammount that you need to tilt the phone to get full speed
int ydeadzone = 10; //adjust to configure the deadzone
int xdeadzone = 5;

int process = 0;
int drive = 0;

ZumoMotors motors;

int leftspeed = 0;
int rightspeed = 0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  Serial.println("Entering Loop");

  // set the data rate for the SoftwareSerial port
  BT.begin(9600);
}

void loop() // run over and over
{

  BTGet(); 
  if(process == 1) BTProcess();
  if(drive ==1) MotorDrive();

}

void BTGet()
{
  
  if(BT.available() > 10) // Make sure that we have already received enough information 
  {
    Serial.println(millis());
    in = BT.read(); // Read the first character in the buffer
    if(in != 'Y') // If it does not equal the first character that we are expecting
    {
      while(in != 'Y') // then read from the buffer until it does
      {
        in = BT.read();
      }
    }
    data[0] = in; // once it does then store it in the first position in the array


    for(int i=1; i<10; i++) // read the next 9 characters in the buffer and store them in the array
    {
      data[i] = BT.read();
    }

    for(int i=0; i<10; i++) //for debugging purposes print these characters out the serial port
    {
      Serial.write(data[i]);
    }
    Serial.println();
    process = 1;
  }

}

void BTProcess()
{
  process = 0;

  if(data[1] == 70) ydir = 1; // determine whether the X and Y values should be negative or positive depenging based on whether the robot has recieved a F or B / L or R
  if(data[1] == 66) ydir = 0;
  if(data[6] == 76) xdir = 1; //left
  if(data[6] == 82) xdir = 0; //right

  yval = ((data[2]-48)*100)+((data[3]-48)*10)+(data[4]-48); // add the seperate values for 1's 10's and 100's together to get one int that represents the recieved number
  xval = ((data[7]-48)*100)+((data[8]-48)*10)+(data[9]-48);
  
  Serial.print("Y UM ");
  Serial.println(yval);
  Serial.print("X UM ");
  Serial.println(xval);
  
  yval = yval - ydeadzone; //sets size of deadzone
  xval = xval - xdeadzone;
  
  if(yval<0) yval = 0; // removes negative numbers created by deadzone
  if(xval<0) xval = 0;

  if(yval>scale) yval=scale; //if the number is larger than X degrees then make it X - this is to set a max value
  if(xval>scale) xval=scale;
  
  Serial.print("Y Dir ");
  Serial.println(ydir);
  Serial.print("X Dir ");
  Serial.println(xdir);
 
  Serial.print("Y M ");
  Serial.println(yval);
  Serial.print("X M ");
  Serial.println(xval);

  yvalmapped = map(yval, 0, scale, 0, 400); //map the recieved values in degrees to the PWM range supported by the motors ie 0 to 50 degrees to 0 to 400 as per the motor driver specs
  xvalmapped = map(xval, 0, scale, 0, 400);

  if(ydir==1) //if going forward
  {
    leftspeed = yvalmapped; //set both motors to go forward
    rightspeed = yvalmapped;
    if(xdir==1) leftspeed = yvalmapped - (((yvalmapped/4)*3)*(xvalmapped/400)); // Then slow the left motor by the percentage out of full speed that we are turning left (based on xvalmapped). Make sure that we never drop below 25% speed
    if(xdir==0) rightspeed = yvalmapped - (((yvalmapped/4)*3)*(xvalmapped/400)); // Then slow the right motor by the percentage out of full speed that we are turning right (based on xvalmapped). Make sure that we never drop below 25% speed
  }

  if(ydir==0) //if going backwards
  {
    yvalmapped = map(yvalmapped, 0, 400, 0, -400); // remap the PWM value for reverse travel
    
    leftspeed = (yvalmapped); //set both motors to go backward
    rightspeed = (yvalmapped);
    if(xdir==1) leftspeed = yvalmapped - (((yvalmapped/4)*3)*(xvalmapped/400)); 
    if(xdir==0) rightspeed = yvalmapped - (((yvalmapped/4)*3)*(xvalmapped/400));
  }
  
  if(yvalmapped==0) //if we're not moving forward or reverse but are turning
  {
    if(xvalmapped>0)
    {
      if(xdir==1)
      {
        leftspeed = (0-xvalmapped);// then take the x value and turn the left and right sides in opposite directions by that ammount
        rightspeed = xvalmapped;
      }
      if(xdir==0)
      {
        leftspeed = xvalmapped;
        rightspeed = (0-xvalmapped);
      }
    }
  }
        
  
  
  
  // the next sections prevents values larger than allowed being sent to one motor. as soon as it overruns it slows or reverses the other motor by the overrun ammount
  
  /* Not currently needed
  if(leftspeed<-400) 
  {
    rightspeed = rightspeed + ((leftspeed+400)*-1);
    leftspeed = -400;
  }

  if(rightspeed<-400) 
  {
    leftspeed = leftspeed + ((rightspeed+400)*-1);
    rightspeed = -400;
  }

  if(leftspeed>400) 
  {
    rightspeed = rightspeed - (leftspeed-400);
    leftspeed = 400;
  }

  if(rightspeed>400)
  {
    leftspeed = leftspeed - (rightspeed-400);
    rightspeed = 400;
  }
*/

  drive = 1;
}

void MotorDrive()
{
  drive = 0;
  Serial.print("Left Speed ");
  Serial.println(leftspeed);
  Serial.print("Right Speed ");
  Serial.println(rightspeed);  
  motors.setLeftSpeed(leftspeed);
  motors.setRightSpeed(rightspeed);
  Serial.println(millis());
  Serial.println();
}
















