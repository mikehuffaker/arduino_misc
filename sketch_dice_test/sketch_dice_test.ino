const unsigned int LED1 = 2;
const unsigned int LED2 = 3;
const unsigned int LED3 = 4;
const unsigned int LED4 = 5;
const unsigned int LED5 = 6;
const unsigned int LED6 = 7;
const unsigned int LED7 = 8;
const unsigned int BTN1 = 10;
const unsigned int delayTime = 250;
int Btn1_PrevState = LOW;
int Btn1_CurrState = LOW;
int rolled = 0;

void setup() {
  
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);
    pinMode(LED6, OUTPUT);
    pinMode(LED7, OUTPUT);    
    pinMode(BTN1, INPUT);
    randomSeed(analogRead(A0));
}

void loop() {
    Btn1_CurrState = digitalRead(BTN1);
    if ( Btn1_CurrState == HIGH ) {
        rolled = random(1,7); 
    
        switch (rolled) {
            case 1:
                showDiceOne();
                break;
            case 2:
                showDiceTwo();
                break;
            case 3:
                showDiceThree();
                break;
            case 4:
                showDiceFour();
                break;
            case 5:
                showDiceFive();
                break;
            case 6:
                showDiceSix();
                break;
        }
        delay(delayTime);    
    }
}

void showDiceOne() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);  
}

void showDiceTwo() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, LOW);  
}

void showDiceThree() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, LOW);  
}

void showDiceFour() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);  
}

void showDiceFive() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);  
}

void showDiceSix() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);  
}
