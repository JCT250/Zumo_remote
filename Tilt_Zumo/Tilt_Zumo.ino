#include <ZumoMotors.h>
#include <SoftwareSerial.h>


SoftwareSerial BT(5, 4); // RX, TX

char in;

int xdir = 0;
int xval = 0;
int xvalmapped = 0;

int ydir = 0;
int yval = 0;
int yvalmapped = 0;

char data[11] = {
  'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O'};

int time = 100;

int process = 0;
int drive = 0;

ZumoMotors motors;

int leftspeed = 0;
int rightspeed = 0;

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Goodnight moon!");

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

  if(data[1] == 70) ydir = 1;
  if(data[1] == 66) ydir = 0;
  if(data[6] == 76) xdir = 1; //left
  if(data[6] == 82) xdir = 0; //right

  yval = ((data[2]-48)*100)+((data[3]-48)*10)+(data[4]-48);
  xval = ((data[7]-48)*100)+((data[8]-48)*10)+(data[9]-48);
  
  yval = yval - 5; //sets size of deadzone
  xval = xval - 5;
  
  if(yval<0) yval = 0; // removes negative numbers
  if(xval<0) xval = 0;

  if(yval>50) yval=50;
  if(xval>50) xval=50;
  
  Serial.print("Y Dir ");
  Serial.println(ydir);
  Serial.print("X Dir ");
  Serial.println(xdir);
 
  Serial.println(yval);
  Serial.println(xval);

  yvalmapped = map(yval, 0, 50, 0, 400);
  xvalmapped = map(xval, 0, 50, 0, 400);

  if(ydir==1) //if going forward
  {
    leftspeed = yvalmapped; //set both motors to go forward
    rightspeed = yvalmapped;
    if(xdir==1) leftspeed = yvalmapped - (2*xvalmapped); //then if there is a left had turn slow the left motor by 2 x the x value
    if(xdir==0) rightspeed = yvalmapped - (2*xvalmapped); //or if there is a right turn slow the right motor by 2 x the x value
  }

  if(ydir==0) //if going backwards
  {
    yvalmapped = map(yvalmapped, 0, 400, 0, -400);
    
    leftspeed = (yvalmapped); //set both motors to go backward
    rightspeed = (yvalmapped);
    if(xdir==1) leftspeed = (yvalmapped) + (2*xvalmapped); //then if there is a left had turn slow the left motor by 2 x the x value
    if(xdir==0) rightspeed = (yvalmapped) + (2*xvalmapped); //or if there is a right turn slow the right motor by 2 x the x value
  }
  
  if(yvalmapped==0) //if we're not moving forward or reverse but are turning
  {
    if(xvalmapped>0)
    {
      if(xdir==1)
      {
        leftspeed = (0-xvalmapped);
        rightspeed = xvalmapped;
      }
      if(xdir==0)
      {
        leftspeed = xvalmapped;
        rightspeed = (0-xvalmapped);
      }
    }
  }
        
  
  // the next sections prevents values larger than allowed being sent to one motor. as soon as it overruns it slows or reverses the other motor
  
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

  drive = 1;
}

void MotorDrive()
{
  drive = 0;
  Serial.print("Left Speed ");
  Serial.println(leftspeed);
  Serial.print("Right Speed ");
  Serial.println(rightspeed);
  Serial.println();
  
  motors.setLeftSpeed(leftspeed);
  motors.setRightSpeed(rightspeed);
  
}
















