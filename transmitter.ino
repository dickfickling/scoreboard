// RF Link using VirtualWire to Transmit messages
// simplex (one-way) receiver with a 315MHz RF Link Transmitter module
// tx pin 3 on Duemilanova (arduino)

 
#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder
#undef int
#undef abs
#undef double
#undef float
#undef round

int green = 9;
byte greenScore = 0;
int greenDiff = 0; // number of ms since last time we recorded a point for button1


int red = 8;
byte redScore = 0;
int redDiff = 0; // number of ms since last time we recorded a point for button1



void setup()
{
  Serial.begin(9600);
    pinMode(green, INPUT);
    digitalWrite(green, HIGH);
    pinMode(red, INPUT);
    digitalWrite(red, HIGH);
    
     // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for RF Link module
    vw_setup(2000);                 // Bits per sec
    vw_set_tx_pin(3);                // pin 3 is used as the transmit data out into the TX Link module, change this to suit your needs. 
}


int lastGreen = 0;
int lastRed = 0;
void loop()
{
  int currentGreen = digitalRead(green);
  int currentRed = digitalRead(red);
  

  if (lastGreen == 1 && currentGreen == 0) {
    if (greenDiff < 300) {
      greenScore = 0;
    } else {
      greenScore++;
      greenDiff = 0;
    }
  }

  if (lastRed == 1 && currentRed == 0) {
    if (redDiff < 300) {
      redScore = 0;
    } else {
      redScore++;
      redDiff = 0;
    }
  }
  
  redDiff += 30;
  greenDiff += 30;
  lastGreen = currentGreen;
  lastRed = currentRed;

  String greenMsg = "g:" + String(greenScore);
  int greenLen = greenMsg.length() + 1;
  String redMsg   = "r:" + String(redScore);
  int redLen = redMsg.length() + 1;

  char greenBuf[greenLen];
  char redBuf[redLen];

  greenMsg.toCharArray(greenBuf, greenLen);
  redMsg.toCharArray(redBuf, redLen);

   vw_send((uint8_t *)greenBuf, greenLen);
   vw_send((uint8_t *)redBuf, redLen);
}
