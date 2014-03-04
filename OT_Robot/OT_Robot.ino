// Simple robot to be used for OT purposes. Contains code 
// from Pololu Buzzer examples (www.pololu.com) 

#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(5, 4); // RX, TX

byte in;
int time = 100;

ZumoBuzzer buzzer;
ZumoMotors motors;

#include <avr/pgmspace.h>  // this lets us refer to data in program space (i.e. flash)
// store this fugue in program space using the PROGMEM macro.  
// Later we will play it directly from program space, bypassing the need to load it 
// all into RAM first.
const char fugue[] PROGMEM = 
"! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
"O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
"L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
"ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
"O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
"<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
"<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
"O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
"e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";


void setup()
{
  Serial.begin(9600);
  Serial.println("Entering Loop");
  BT.begin(9600);
}

void loop()
{

  if (BT.available())
  {
    in = BT.read();
    //Serial.println(in);
    if(in == 68) //Go
    {
      Serial.println("Driving");
      buzzer.playFromProgramSpace(fugue);
      motors.setLeftSpeed(100);
      motors.setRightSpeed(400);
    }

    if(in == 85) // Stop
    {
      Serial.println("Stopping");
      buzzer.stopPlaying();
      motors.setLeftSpeed(0);
      motors.setRightSpeed(0);
    }
  }
}


