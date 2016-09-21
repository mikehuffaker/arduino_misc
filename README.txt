
This repository contains misc sketch code to drive an Arduino micro-controller
board.  These are all just test sketches.  I'm sharing them as open source, in
case anyone is interested, however be advised that none of these sketches will
 work unless you have the arduino wired up correctly with the correct supporting
electronic components.  

Also note that although I am sharing this code as Open Source, please 
respect the BSD license terms, as stated in the LICENSE.txt file.

joytest_GD_nunchuck - test program to test Nunchuck Wii control arduino library
I coded.  Requires Arduino connected to Wii Nunchuck and GameDuino sheild. 
Wii can be used to move cursor object ( a sprite ) around the screen and the
 x/y values will also be displayed.

sketch_dice_text - this was a program where I had put 7 LED's into a board in  
the pattern of a 6 sided dice.  There was also a button wired up to the board 
and by pressing the button, the program would call the random function to get
a number between 1 and 6 to set the dice.  It was a very simple program, but
one of the first ones I did when I was learning about the Arduino and how to
connect up electronic hardware to it.

Below is how the LED's would light up for 1 upto 6, similar to the 6 sided 
dice that is standard in many board games:

0   0    0   1    0   1    1   1    1   1    1   1
0 1 0    0 0 0    0 1 0    0 0 0    0 1 0    1 0 1
0   0    1   0    1   0    1   1    1   1    1   1

sketch_led_multi - very simple sketch that I wrote to test a single three color
LED connected to an Arduino.  The program basically just randomly picks a
 number which is then used to pull a color from an array of colors.  This LED 
could only handle Red, Blue, or Green being On or Off, so the color 
combinations are very simple - there is only 8 of them in this program and each
element of the array is basically 3 boolean values for Red, Blue, or Green.

sketch_light_strip_test - earlier version of the holiday lights project I used
when testing with WS2801 LED light strips.  Note this uses a library I
 downloaded from Adafruit to control the WS2801, and I thank Adafruit for 
making code like this available.

sketch_nunchuck_test - simple test program for reading a Wii nunchuck connected
to an Arduino and printing values to the test console over a serial port.

