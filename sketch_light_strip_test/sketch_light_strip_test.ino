#include <Adafruit_WS2801.h>
#include <SPI.h>
#include <LiquidCrystal.h>

// Note - Pins 3,5,10,11,12,13 used by wi-fi card, so using 
// 4 and 6 to communicate with the LED strand and 2 for button
const int dataPin = 4;
const int clockPin = 6;
const int buttonApin = 2;

const int brightnessPin = A2;
 
// LEDMode starts at mode 1
int LEDMode = 7;
const int LEDModeMax = 7;

//  Brightness reduction factor, controlled by variable resister knob
// int dimmingLevel = 0;

// timestamp for button push timer
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

unsigned long startUpMsgDelay = 7000;

boolean breakLEDMode = false;

// Using some analog pins to free up for sensor/Wi-FI
// A0 must be free for future microphone use
LiquidCrystal lcd(7, 8, 9, 17, 18, 19);

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
Adafruit_WS2801 strip = Adafruit_WS2801(100 , dataPin, clockPin);
  
void setup()
{
    pinMode(buttonApin, INPUT_PULLUP);

    strip.begin();
    // Update LED contents, to start they are all 'off'
    strip.show();
    
    // Interrupt for button push - 0 is pin 2, 1 is pin 3
    attachInterrupt( 0, buttonCheck, LOW );
    
    lcd.begin(16, 2);
    // Print a message to the LCD.
     lcd.setCursor(0, 0);
    lcd.print("Mike's");
    lcd.setCursor(0, 1);
    lcd.print("Holiday Lights!");
}
    
// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait, char oddEvenAll, char beginOrEnd )
{
    int i;
    
    if ( ( !beginOrEnd || beginOrEnd == 'B' ) && !breakLEDMode )
    {
        for ( i=0; i < strip.numPixels(); i++ )
        {
            if ( oddEvenAll == 'A' )
            {
                strip.setPixelColor(i, c);
            }
            else if ( oddEvenAll == 'E' and i % 2 == 0 )
            {
                strip.setPixelColor(i, c);
            }
            else if ( oddEvenAll == 'O' and i % 2 == 1 )
            {
                strip.setPixelColor(i, c);
            }
        
            if ( !breakLEDMode )
            {
                strip.show();
                delay(wait);
            }
        }
    }
    else if ( beginOrEnd == 'E' && !breakLEDMode )
    {
        for ( i = strip.numPixels(); i > -1; i-- )
        {
            if ( oddEvenAll == 'A' )
            {
                strip.setPixelColor(i, c);
            }
            else if ( oddEvenAll == 'E' and i % 2 == 0 )
            {
                strip.setPixelColor(i, c);
            }
            else if ( oddEvenAll == 'O' and i % 2 == 1 )
            {
                strip.setPixelColor(i, c);
            }
        
            if ( !breakLEDMode )
            {
                strip.show();
                delay(wait);
            }
        }
    }
}

// set 2 colors down the strip, alternating
void colorSet2(uint32_t color1, uint32_t color2, int wait ) 
{
    int i;
    
    for ( i=0; i < strip.numPixels(); i++ )
    {
        if ( ( i % 2 ) == 1 )
        {
            strip.setPixelColor(i, color1);            
        }
        else if ( ( i % 2 ) == 0 )
        {
            strip.setPixelColor(i, color2);            
        }
    }
    if ( !breakLEDMode )
    {
        strip.show();
        delay(wait);
    }
}

// set 3 colors down the strip, alternating
void colorSet3(uint32_t color1, uint32_t color2, uint32_t color3, int wait ) 
{
    int i;
    
    for ( i=0; i < strip.numPixels(); i++ )
    {
        //strip.setPixelColor(i, color1);
        if ( ( i % 3 ) == 2 )
        {
            strip.setPixelColor(i, color1);            
        }
        else if ( ( i % 3 ) == 1 )
        {
            strip.setPixelColor(i, color2);            
        }
        else if ( ( i % 3 ) == 0 )
        {
            strip.setPixelColor(i, color3);            
        }
    }
    if ( !breakLEDMode )
    {
        strip.show();
        delay(wait);
    }
}

// set 2 colors, strip is first color and then 2nd color "chases" up and down the strip
void colorChase2(uint32_t color1, uint32_t color2, int wait )
{
    int i;
    int j;
    
    //initialize with one color
    for ( i=0; i < strip.numPixels() && !breakLEDMode; i++ )
    {
        if ( i == 0 )
            strip.setPixelColor(i, color2);
        else
            strip.setPixelColor(i, color1);
    }
    
    if ( !breakLEDMode )
    {
        strip.show();
        delay(wait);
    }
    
    // start at beginning
    for ( j=0; j < strip.numPixels() && !breakLEDMode; j++ )
    {
        for ( i=0; i < strip.numPixels(); i++ )
        {
            if ( i == j )
                strip.setPixelColor(i, color2);
            else
                strip.setPixelColor(i, color1);
        }
        
        if ( !breakLEDMode )
        {
            strip.show();
            delay(wait);
        }
    }
    
    // bring it back
    for ( j=strip.numPixels(); j > 0 && !breakLEDMode; j-- )
    {
        for ( i=0; i < strip.numPixels(); i++ )
        {
            if ( i == j )
                strip.setPixelColor(i, color2);
            else
                strip.setPixelColor(i, color1);
        }
        
        if ( !breakLEDMode )
        {
            strip.show();
            delay(wait);
        }
    }
}

// randomly set a LED to one of 2 colors down the strip for a twinkle
// effect
void twinkle2(uint32_t color1, uint32_t color2, int wait, int iterations )
{
    int i;
    int c;
    
    for ( int x = 0; x < iterations && !breakLEDMode; x++ )
    {
        i = random(0, strip.numPixels());
        c = random(0,2);

        if ( c == 1 )
            strip.setPixelColor(i, color2);
        else
            strip.setPixelColor(i, color1);
            
        if ( !breakLEDMode )
        {
            strip.show();
            delay(wait);
        }
    }   
 }

// randomly set a LED to one of 3 colors down the strip for a twinkle
// effect
void twinkle3(uint32_t color1, uint32_t color2, uint32_t color3, int wait, int iterations )
{
    int i;
    int c;
    
    for ( int x = 0; x < iterations && !breakLEDMode; x++ )
    {
        i = random(0, strip.numPixels());
        c = random(0,3);

        if ( c == 2 )
            strip.setPixelColor(i, color3);
        else if ( c == 1 )
            strip.setPixelColor(i, color2);
        else
            strip.setPixelColor(i, color1);
            
        if ( !breakLEDMode )
        {
            strip.show();
            delay(wait);
        }
    }   
 }

/* Helper functions */
// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
    uint32_t c;
    c = r;
    c <<= 8;
    c |= g;
    c <<= 8;
    c |= b; 
    return c;
}
 
uint32_t getRealColor( String colorName )
{
  
    // When the color is set, read the analog port to check the variable resistor 
    // and see if the brightness was turned down.
    
    uint32_t dimmingLevel = checkBrightnessLevel();
    
    if ( colorName == "RED" )
    {
        return Color( 255 - dimmingLevel, 0, 0 );
    }
    else if ( colorName == "ORANGE" )
    {
        return Color( 255 - dimmingLevel, 60 - (dimmingLevel / 4), 0) ;
    }
    else if ( colorName == "BLUE" )
    {
        return Color( 0, 0, 255 - dimmingLevel );
    }
    else if ( colorName == "GREEN" )
    {
        return Color( 0, 255 - dimmingLevel, 0 );
    }
    else if ( colorName == "SEAGREEN" )
    {
        return Color( 0, 255 - dimmingLevel, 64 - (dimmingLevel / 4) );
    }
    else if ( colorName == "YELLOW" )
    {
        return Color( 128 - (dimmingLevel / 2), 128 - (dimmingLevel / 2), 0 );
    }
    else if ( colorName == "SILVER" )
    {
        return Color( 180 - dimmingLevel, 190 - dimmingLevel, 190 - dimmingLevel );
    }
    else if ( colorName == "CYAN" )
    {
        return Color( 0, 128 - (dimmingLevel / 2), 128 - (dimmingLevel / 2));
    }
    else if ( colorName == "MAGENTA" )
    {
        return Color( 128 - (dimmingLevel / 2), 0, 128 - (dimmingLevel / 2) );
    }
    else if ( colorName == "PINK" )
    {
        return Color( 255 - dimmingLevel, 100 - (dimmingLevel / 2), 175 - dimmingLevel );
    }
    else if ( colorName == "WHITE" )
    {
        return Color( 200 - dimmingLevel, 200 - dimmingLevel, 200 - dimmingLevel );
    }
}

uint32_t checkBrightnessLevel( )
{
    int analogLevel =  analogRead(brightnessPin);
    int reduction = ( analogLevel + 1 ) / 12 ;
    return reduction;
}

uint32_t getRandomColor( )
{
    int x = random( 1,7 );
    
    if ( x == 1 )
       return getRealColor( "RED" );
    else if ( x == 2 )
        return getRealColor( "BLUE" );
    else if ( x == 3 )
        return getRealColor( "GREEN" );
    else if ( x == 4 )
        return getRealColor( "YELLOW" );
    else if ( x == 5 )
        return getRealColor( "CYAN" );
    else if ( x == 6 )
        return getRealColor( "MAGENTA" );
}

void buttonCheck()
{
    // breakLEDMode tells the current light loop to break and also by checking 
    // for false here, it prevents the mode from skipping ahead until the 
    // current mode is finished and the next one started.
    if ( digitalRead(buttonApin) == LOW and breakLEDMode == false )
    {
        LEDMode++;
        breakLEDMode = true;
        if ( LEDMode > LEDModeMax )
        {
            LEDMode = 1;
        }
    }
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("New Blink MODE");
}

void ColorTest1()
{
    breakLEDMode = false;

    if ( millis() > startUpMsgDelay )
    {    
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ColorTest1 MODE");
    }

    while ( breakLEDMode != true )
    {
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***RED***");
        }
        colorWipe(getRealColor( "RED" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***ORANGE***");
        }
        colorWipe(getRealColor( "ORANGE" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***BLUE***");
        }
        colorWipe(getRealColor( "BLUE" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***GREEN***");
        }
        colorWipe(getRealColor( "GREEN" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***SEAGREEN***");
        }
        colorWipe(getRealColor( "SEAGREEN" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***YELLOW***");
        }
        colorWipe(getRealColor( "YELLOW" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***SILVER***");
        }
        colorWipe(getRealColor( "SILVER" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***CYAN***");
        }
        colorWipe(getRealColor( "CYAN" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***MAGENTA***");
        }
        colorWipe(getRealColor( "MAGENTA" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***PINK***");
        }
        colorWipe(getRealColor( "PINK" ), 25, 'A', 'B' );
        if ( millis() > startUpMsgDelay )
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("ColorTest1 MODE");
            lcd.setCursor(0, 1);
            lcd.print("***WHITE***");
        }
        colorWipe(getRealColor( "WHITE" ), 25, 'A', 'B' );
    }
}

void RandomColor1()
{
    breakLEDMode = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RandomColor1 MODE");

    while ( breakLEDMode != true )
    {
        colorWipe(getRandomColor(), 30, 'O', 'B');
        colorWipe(getRandomColor(), 30, 'E', 'B');
    }
}

void RandomColor2()
{
    breakLEDMode = false;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RandomColor2 MODE");

    while ( breakLEDMode != true )
    {
        colorWipe(getRandomColor(), 15, 'A', 'B');
    }
}

// Run multiple MODES for christmas
void ChristmasProgram1()
{
    breakLEDMode = false;
    int x = 0;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Christmas1 MODE");

    while ( breakLEDMode != true )
    {
        for ( x = 0; x < 2 && breakLEDMode != true; x++ )
        {       
            colorWipe(getRealColor( "RED"), 15, 'A', 'B' );
            colorWipe(getRealColor( "GREEN"), 15, 'A', 'E' );
            colorWipe(getRealColor( "BLUE"), 15, 'A', 'B' );
            colorWipe(getRealColor( "RED"), 15, 'A', 'E' );
            colorWipe(getRealColor( "GREEN"), 15, 'A', 'B' );
            colorWipe(getRealColor( "BLUE"), 15, 'A', 'E' );
        }
        
        for ( x = 0; x < 8 && breakLEDMode != true; x++ )
        { 
            colorSet3(getRealColor("RED"), getRealColor("BLUE"), getRealColor("GREEN"), 1000); // red fill
            colorSet3(getRealColor("BLUE"), getRealColor("GREEN"), getRealColor("RED"), 1000); // red fill
            colorSet3(getRealColor("GREEN"), getRealColor("RED"), getRealColor("BLUE"), 1000); // red fill
        }
   
        colorChase2(getRealColor("RED"), getRealColor("GREEN"), 20 );
        colorChase2(getRealColor("GREEN"), getRealColor("RED"), 20 );
        colorChase2(getRealColor("BLUE"), getRealColor("RED"), 20 );
        
        twinkle3(getRealColor("RED"), getRealColor("BLUE"), getRealColor("GREEN"), 50, 400 );
    }
}

void HalloweenProgram1()
{
    breakLEDMode = false;
    int x = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Halloween1 MODE");

    while ( breakLEDMode != true )
    {
        for ( x = 0; x < 2 && breakLEDMode != true; x++ )
        {       
            colorWipe(getRealColor( "ORANGE"), 15, 'A', 'B' );
            colorWipe(getRealColor( "WHITE"), 15, 'A', 'E' );
            colorWipe(getRealColor( "RED"), 15, 'A', 'B' );
            colorWipe(getRealColor( "ORANGE"), 15, 'A', 'E' );
            colorWipe(getRealColor( "WHITE"), 15, 'A', 'B' );
            colorWipe(getRealColor( "RED"), 15, 'A', 'E' );
        }
        
        for ( x = 0; x < 4 && breakLEDMode != true; x++ )
        { 
            colorSet3(getRealColor("ORANGE"), getRealColor("WHITE"), getRealColor("RED"), 1000); // red fill
            colorSet3(getRealColor("WHITE"), getRealColor("RED"), getRealColor("ORANGE"), 1000); // red fill
            colorSet3(getRealColor("RED"), getRealColor("ORANGE"), getRealColor("WHITE"), 1000); // red fill
        }

        for ( x = 0; x < 4 && breakLEDMode != true; x++ )
        { 
            colorSet3(getRealColor("ORANGE"), getRealColor("WHITE"), getRealColor("RED"), 500); // red fill
            colorSet3(getRealColor("WHITE"), getRealColor("RED"), getRealColor("ORANGE"), 500); // red fill
            colorSet3(getRealColor("RED"), getRealColor("ORANGE"), getRealColor("WHITE"), 500); // red fill
        }
   
        colorChase2(getRealColor("ORANGE"), getRealColor("WHITE"), 20 );
        colorChase2(getRealColor("WHITE"), getRealColor("RED"), 20 );
        colorChase2(getRealColor("RED"), getRealColor("ORANGE"), 20 );
        
        twinkle3(getRealColor("ORANGE"), getRealColor("WHITE"), getRealColor("RED"), 50, 400 );
    }
}

void July4thProgram1()
{
    breakLEDMode = false;
    int x = 0;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("July4th1 MODE");

    while ( breakLEDMode != true )
    {
        for ( x = 0; x < 2 && breakLEDMode != true; x++ )
        {       
            colorWipe(getRealColor( "RED"), 15, 'A', 'B' );
            colorWipe(getRealColor( "WHITE"), 15, 'A', 'E' );
            colorWipe(getRealColor( "BLUE"), 15, 'A', 'B' );
            colorWipe(getRealColor( "RED"), 15, 'A', 'E' );
            colorWipe(getRealColor( "WHITE"), 15, 'A', 'B' );
            colorWipe(getRealColor( "BLUE"), 15, 'A', 'E' );
        }
        
        for ( x = 0; x < 4 && breakLEDMode != true; x++ )
        { 
            colorSet3(getRealColor("RED"), getRealColor("WHITE"), getRealColor("BLUE"), 1000); // red fill
            colorSet3(getRealColor("BLUE"), getRealColor("RED"), getRealColor("WHITE"), 1000); // red fill
            colorSet3(getRealColor("WHITE"), getRealColor("BLUE"), getRealColor("RED"), 1000); // red fill
        }
        
        for ( x = 0; x < 4 && breakLEDMode != true; x++ )
        {
            colorSet3(getRealColor("RED"), getRealColor("WHITE"), getRealColor("BLUE"), 500 ); // red fill
            colorSet3(getRealColor("BLUE"), getRealColor("RED"), getRealColor("WHITE"), 500); // red fill
            colorSet3(getRealColor("WHITE"), getRealColor("BLUE"), getRealColor("RED"), 500); // red fill
        }
   
        colorChase2(getRealColor("RED"), getRealColor("WHITE"), 20 );
        colorChase2(getRealColor("WHITE"), getRealColor("BLUE"), 20 );
        colorChase2(getRealColor("BLUE"), getRealColor("RED"), 20 );
        
        twinkle3(getRealColor("RED"), getRealColor("WHITE"), getRealColor("BLUE"), 50, 400 );
    }
}

void ChanukahProgram1()
{
    breakLEDMode = false;
    int x = 0;
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Chanukah1 MODE");

    while ( breakLEDMode != true )
    {
        for ( x = 0; x < 2 && breakLEDMode != true; x++ )
        {       
            colorWipe(getRealColor( "BLUE"), 15, 'A', 'B' );
            colorWipe(getRealColor( "SILVER"), 15, 'A', 'E' );
            colorWipe(getRealColor( "BLUE"), 15, 'A', 'B' );
            colorWipe(getRealColor( "SILVER"), 15, 'A', 'E' );
        }
        
        for ( x = 0; x < 4 && breakLEDMode != true; x++ )
        { 
            colorSet2(getRealColor("BLUE"), getRealColor("SILVER"), 1000);
            colorSet2(getRealColor("SILVER"), getRealColor("BLUE"), 1000);
        }
        
        for ( x = 0; x < 4 && breakLEDMode != true; x++ )
        {
            colorSet2(getRealColor("SILVER"), getRealColor("BLUE"), 1000);
            colorSet2(getRealColor("BLUE"), getRealColor("SILVER"), 1000);
        }
   
        colorChase2(getRealColor("BLUE"), getRealColor("SILVER"), 20 );
        colorChase2(getRealColor("SILVER"), getRealColor("BLUE"), 20 );
        
        twinkle2(getRealColor("BLUE"), getRealColor("SILVER"), 50, 400 );
    }
}

void loop ()
{
    restart_loop:
    // testswitch sets the program.  Maybe in the future use a switch on the arduino to control
    // the program and led readout to show the playing program
    // int testSwitch = 1;
    // LEDMode = 3;
    if ( LEDMode == 1)
    {
        ColorTest1();
    }
    if ( LEDMode == 2 )
    {
        RandomColor1();
    }
    else if ( LEDMode == 3 )
    {
        RandomColor2();
    }
    else if ( LEDMode == 4 )
    {
        July4thProgram1();
    }
    else if ( LEDMode == 5 )
    {
        HalloweenProgram1();
    }
    else if ( LEDMode == 6 )
    {
        ChanukahProgram1();
    }
    else if ( LEDMode == 7 )
    {
        ChristmasProgram1();
    }

}

