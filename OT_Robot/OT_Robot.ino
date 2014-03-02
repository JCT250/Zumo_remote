#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <SoftwareSerial.h>
#define MELODY_LENGTH 95

SoftwareSerial BT(5, 4); // RX, TX

unsigned char currentIdx;
byte in;
int time = 100;

// These arrays take up a total of 285 bytes of RAM (out of a limit of 1k (ATmega168), 2k (ATmega328), or 2.5k(ATmega32U4))
unsigned char note[MELODY_LENGTH] = 
{
  NOTE_E(5), SILENT_NOTE, NOTE_E(5), SILENT_NOTE, NOTE_E(5), SILENT_NOTE, NOTE_C(5), NOTE_E(5),
  NOTE_G(5), SILENT_NOTE, NOTE_G(4), SILENT_NOTE,

  NOTE_C(5), NOTE_G(4), SILENT_NOTE, NOTE_E(4), NOTE_A(4), NOTE_B(4), NOTE_B_FLAT(4), NOTE_A(4), NOTE_G(4),
  NOTE_E(5), NOTE_G(5), NOTE_A(5), NOTE_F(5), NOTE_G(5), SILENT_NOTE, NOTE_E(5), NOTE_C(5), NOTE_D(5), NOTE_B(4),

  NOTE_C(5), NOTE_G(4), SILENT_NOTE, NOTE_E(4), NOTE_A(4), NOTE_B(4), NOTE_B_FLAT(4), NOTE_A(4), NOTE_G(4),
  NOTE_E(5), NOTE_G(5), NOTE_A(5), NOTE_F(5), NOTE_G(5), SILENT_NOTE, NOTE_E(5), NOTE_C(5), NOTE_D(5), NOTE_B(4),

  SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE,
  NOTE_G_SHARP(4), NOTE_A(4), NOTE_C(5), SILENT_NOTE, NOTE_A(4), NOTE_C(5), NOTE_D(5),

  SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE,
  NOTE_C(6), SILENT_NOTE, NOTE_C(6), SILENT_NOTE, NOTE_C(6),

  SILENT_NOTE, NOTE_G(5), NOTE_F_SHARP(5), NOTE_F(5), NOTE_D_SHARP(5), NOTE_E(5), SILENT_NOTE,
  NOTE_G_SHARP(4), NOTE_A(4), NOTE_C(5), SILENT_NOTE, NOTE_A(4), NOTE_C(5), NOTE_D(5),

  SILENT_NOTE, NOTE_E_FLAT(5), SILENT_NOTE, NOTE_D(5), NOTE_C(5)
  };

  unsigned int duration[MELODY_LENGTH] =
{
  100, 25, 125, 125, 125, 125, 125, 250, 250, 250, 250, 250,

  375, 125, 250, 375, 250, 250, 125, 250, 167, 167, 167, 250, 125, 125,
  125, 250, 125, 125, 375,

  375, 125, 250, 375, 250, 250, 125, 250, 167, 167, 167, 250, 125, 125,
  125, 250, 125, 125, 375,

  250, 125, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 125, 125,

  250, 125, 125, 125, 250, 125, 125, 200, 50, 100, 25, 500,

  250, 125, 125, 125, 250, 125, 125, 125, 125, 125, 125, 125, 125, 125,

  250, 250, 125, 375, 500
};

ZumoBuzzer buzzer;
ZumoMotors motors;


void setup()                    // run once, when the sketch starts
{
  currentIdx = 0;
  Serial.begin(9600);
  Serial.println("Goodnight moon!");
  BT.begin(9600);
}

void loop()                     // run over and over again
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
      delay(time);
      motors.setLeftSpeed(0);
      motors.setRightSpeed(0);
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
      delay(time);
      motors.setLeftSpeed(0);
      motors.setRightSpeed(0);
    }

    if(in == 83) //Stop
    {
      motors.setLeftSpeed(0);
      motors.setRightSpeed(0);
    }

    if(in == 00) // Play song
    {
      // if we haven't finished playing the song and 
      // the buzzer is ready for the next note, play the next note
      while (currentIdx < MELODY_LENGTH)
      {
        // play note at max volume
        buzzer.playNote(note[currentIdx], duration[currentIdx], 15);
        currentIdx++;
      }
      currentIdx = 0;
    }
  }
}

