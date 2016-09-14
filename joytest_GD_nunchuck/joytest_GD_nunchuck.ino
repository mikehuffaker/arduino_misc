#include <Wire.h>
#include <string.h>
#include <SPI.h>
#include <GD.h>
#include "Nunchuk.h"

unsigned char outbuf[6];		// array to store arduino output
int cnt = 0;

Nunchuk nunchuk;

void setup()
{  
    //Wire.begin ();		// join i2c bus with address 0x52
    //nunchuck_init (); // send the initilization handshake
    nunchuk.initialize();
    
    GD.begin();
    GD.ascii();

    GD.wr16(RAM_SPRPAL + 2 * 255, TRANSPARENT);

    // draw 32 circles into 32 sprite images
    int i;
    for (i = 0; i < 32; i++) {
      GD.wr16(RAM_SPRPAL + 2 * i, RGB(8 * i, 64, 255 - 8 * i));
      int dst = RAM_SPRIMG + 256 * i;
      GD.__wstart(dst);
      byte x, y;
      int r2 = min(i * i, 256);
      for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
          byte pixel;
          if ((x * x + y * y) <= r2)
            pixel = i;    // use color above
          else
            pixel = 0xff; // transparent
          SPI.transfer(pixel);
       }
    }
    GD.__end();
  }
}

void nunchuck_init ()
{
  Wire.beginTransmission (0x52);	// transmit to device 0x52
  Wire.write (0x40);		// sends memory address
  Wire.write (0x00);		// sends sent a zero.  
  Wire.endTransmission ();	// stop transmitting
}

void send_zero ()
{
  Wire.beginTransmission (0x52);	// transmit to device 0x52
  Wire.write (0x00);		// sends one byte
  Wire.endTransmission ();	// stop transmitting
}

// Encode data to format that most wiimote drivers except
// only needed if you use one of the regular wiimote drivers
char nunchuk_decode_byte (char x)
{
  x = (x ^ 0x17) + 0x17;
  return x;
}

void circle(int x, int y, byte a)
{
    byte sprnum = 0;
    GD.sprite(sprnum++, x + 16, y + 16, a, 0, 0);
    GD.sprite(sprnum++, x +  0, y + 16, a, 0, 2);
    GD.sprite(sprnum++, x + 16, y +  0, a, 0, 4);
    GD.sprite(sprnum++, x +  0, y +  0, a, 0, 6);
}

static byte ands = 0x1f, ors = 0x00;

void loop()
{
    nunchuk.update();
    
    char byte1[8] = "";
    char byte2[8] = "";
    char byte6[8] = "";

    if ( nunchuk.joystick_x() < 110 ) {
        sprintf(byte1, "Left   " );
    } else if ( nunchuk.joystick_x() > 140 ) {
        sprintf(byte1, "Right  " );
    }
    else
    {
        sprintf(byte1, "HCenter");
    }
    
    if ( nunchuk.joystick_y() < 110 ) {
        sprintf(byte2, "Down   " );
    } else if ( nunchuk.joystick_y() > 140 ) {
        sprintf(byte2, "Up     " );
    }
    else
    {
        sprintf(byte2, "VCenter");
    }
  
    if ( nunchuk.z_button() && nunchuk.c_button() )
        sprintf( byte6, "zc" );
    else if ( nunchuk.z_button() )
        sprintf( byte6, "z " );
    else if ( nunchuk.c_button() )
        sprintf( byte6, " c" );
    else 
        sprintf( byte6, "  " );

    GD.putstr(30, 24, byte1);
    GD.putstr(30, 25, byte2);
    GD.putstr(30, 26, byte6);
    
    GD.putstr(40, 10, strncmp(byte2,"Up",2) ? "-" : "U");
    GD.putstr(40, 20, strncmp(byte2,"Down",4) ? "-" : "D");
  
    GD.putstr(35, 15, strncmp(byte1,"Left",4) ? "-" : "L");
    GD.putstr(45, 15, strncmp(byte1,"Right",5) ? "-" : "R");

    GD.putstr(17, 24, !strncmp(byte6, "", 2) ? "-" : "S");

    int x = 0;
    int y = 0;

    char msg[20];
    x = int(nunchuk.joystick_x());
    y = int(nunchuk.joystick_y());
    sprintf(msg, "X=%4d, Y=%4d", x, y);
    GD.putstr(0, 36, msg);

    //circle(x / 2, 255 - y / 4, digitalRead(2) ? 15 : 31);
    circle(x, 255 - y, nunchuk.c_button() || nunchuk.z_button() ? 15 : 31);   
}
