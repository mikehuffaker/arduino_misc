
int ledDigitalOne[] = { 9, 10, 11 };

const boolean ON = LOW;
const boolean OFF = HIGH;

const boolean RED[] = {ON, OFF, OFF};
const boolean GREEN[] = {OFF, ON, OFF};
const boolean BLUE[] = {OFF, OFF, ON};
const boolean YELLOW[] = {ON, ON, OFF};
const boolean CYAN[] = {OFF, ON, ON};
const boolean MAGENTA[] = {ON, OFF, ON};
const boolean WHITE[] = {ON, ON, ON};
const boolean BLACK[] = {OFF, OFF, OFF};

const boolean* COLORS[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK};

void setup()
{
  for ( int i = 0; i < 3; i++ )
  {
    pinMode( ledDigitalOne[i], OUTPUT );
  }
}

void loop()
{
  //setColor( ledDigitalOne, CYAN );
  randomColor();
}

void randomColor()
{
  int rand = random(0, sizeof(COLORS) / 2);
  setColor( ledDigitalOne, COLORS[rand]);
  delay( 300 );
}

void setColor( int* led, const boolean* color )
{
  for( int i = 0; i < 3; i++ )
  {
    digitalWrite( led[i], color[i] );
  }
}


