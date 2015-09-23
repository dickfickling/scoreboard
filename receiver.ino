#include <VirtualWire.h>  // you must download and install the VirtualWire.h to your hardware/libraries folder
#undef int
#undef abs
#undef double
#undef float
#undef round

#include <SmartMatrix.h>

SmartMatrix matrix;

const int defaultBrightness = 100*(255/100);    // full brightness
//const int defaultBrightness = 15*(255/100);    // dim: 15% brightness
const int defaultScrollOffset = 6;
const rgb24 defaultBackgroundColor = {0x40, 0, 0};

const int numbersWidth = 15;
const int numbersHeight = 31;

static const uint8_t numbers[][64] = {
  {
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,X_______,
__XXXXXX,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
_______X,X_______,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,____XX__,
__XX____,____XX__,
________,____XX__,
________,__XXXX__,
________,__XXXX__,
________,XXX_____,
________,XXX_____,
______XX,X_______,
______XX,X_______,
____XXX_,________,
____XXX_,________,
__XXXX__,________,
__XXXX__,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,XXXXXX__,
________,XXXXXX__,
________,____XX__,
________,____XX__,
________,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,XX______,
__XX____,XX______,
__XX____,XX______,
__XX____,XX______,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,XX______,
________,XX______,
________,XX______,
________,XX______,
________,XX______,
________,XX______,
________,XX______,
________,XX______,
________,XX______,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XX____,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
},
{
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
________,____XX__,
__XX____,____XX__,
__XX____,____XX__,
__XXXXXX,XXXXXX__,
__XXXXXX,XXXXXX__,
________,________,
________,________,
________,________,
________,________,
________,________,
________,________,
}
};

// the setup() method runs once, when the sketch starts
void setup() {


Serial.begin(9600);    

// Initialise the IO and ISR
    vw_set_ptt_inverted(true);    // Required for RX Link Module
    vw_setup(2000);                   // Bits per sec
    vw_set_rx_pin(11);           // We will be receiving on pin 23 (Mega) ie the RX pin from the module connects to this pin. 
    vw_rx_start();                      // Start the receiver

    
matrix.begin();
    matrix.setBrightness(defaultBrightness);

    matrix.setScrollOffsetFromEdge(defaultScrollOffset);

    matrix.setColorCorrection(cc24);
    
}

int red = 0;
int green = 0;

void loop() {
uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) // check to see if anything has been received
    {
     // Message with a good checksum received.
    if (buf[0] == 'r') {
      red = 0;
      red += buf[2] - '0';
      if (buf[3] >= '0') {
        red *= 10;
        red += buf[3] - '0';
      }
    } else if (buf[0] == 'g') {
      green = 0;
      green += buf[2] - '0';
      if (buf[3] >= '0') {
        green *= 10;
        green += buf[3] - '0';
      }
    }
    Serial.println("Red: " + String(red) + " green: " + String(green));
    }

     
        matrix.fillScreen({0, 0, 0});

     matrix.drawMonoBitmap(0,0,numbersWidth,numbersHeight, {0xFF,0,0}, numbers[red/10]);
     matrix.drawMonoBitmap(16,0,numbersWidth,numbersHeight, {0xFF,0,0}, numbers[red % 10]);

     
     matrix.drawMonoBitmap(32,0,numbersWidth,numbersHeight, {0,0xFF,0}, numbers[green / 10]);
     matrix.drawMonoBitmap(48,0,numbersWidth,numbersHeight, {0,0xFF,0}, numbers[green % 10]);
            matrix.swapBuffers(true);
            delay(100);
}
