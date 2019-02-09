// ATMEL ATTINY84 / ARDUINO
//                           +-\/-+
//                     VCC  1|    |14  GND
//             (D 10)  PB0  2|    |13  AREF (D  0)
//             (D  9)  PB1  3|    |12  PA1  (D  1) 
//                     PB3  4|    |11  PA2  (D  2) 
//  PWM  INT0  (D  8)  PB2  5|    |10  PA3  (D  3) 
//  PWM        (D  7)  PA7  6|    |9   PA4  (D  4) 
//  PWM        (D  6)  PA6  7|    |8   PA5  (D  5)        PWM
//                           +----+
// 0 1 2 3 == leds  4 == power module
// 10 9 8 7 6 == buttons

uint32_t ticks = 0;
uint32_t shutdownticks = 600000L;
bool powerbuttonreleased = false;
bool buttonreleased = true;
bool shutdownonrelease = false;

void setup() 
{
  pinMode(0, OUTPUT); // transistor led 1
  pinMode(1, OUTPUT); // transistor led 2
  pinMode(2, OUTPUT); // transistor led 3
  pinMode(3, OUTPUT); // transistor led 4
  pinMode(4, OUTPUT); // pin 5 power module
  digitalWrite(4,LOW); // power modul anlassen
  digitalWrite(0,HIGH); // leds ein
  digitalWrite(1,HIGH); // leds ein
  digitalWrite(2,HIGH); // leds ein
  digitalWrite(3,HIGH); // leds ein
  pinMode(6, INPUT); // power button
  pinMode(7, INPUT); // led button
  pinMode(8, INPUT); // led button
  pinMode(9, INPUT); // led button
  pinMode(10, INPUT); // led button
  ticks = 0; // zeitmessung start
  powerbuttonreleased = false;
  buttonreleased = true; 
  shutdownonrelease = false;  
}

bool pin6pressed = false;

void shutdownattiny()
{
  // leds aus
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(50);
  // power modul aus
  digitalWrite(4,HIGH); 
  delay(200);
}

void loop() 
{
  if( ticks > shutdownticks )
  {
    shutdownattiny();
  }  
  int valu = analogRead(6);
  if(valu < 50)
  {
    pin6pressed = true;
  }
  else
  {
    pin6pressed = false;
  }
  if(powerbuttonreleased && pin6pressed)
  {
    shutdownonrelease = true;
  }
  if(!pin6pressed)
  {
    if(shutdownonrelease)
    {
      shutdownattiny();    
    }
    powerbuttonreleased = true;
  }
  if(digitalRead(7) == HIGH && buttonreleased)
  {
    digitalWrite(0,!digitalRead(0));
    ticks = 0;
    buttonreleased = false;
  }
  if(digitalRead(8) == HIGH && buttonreleased)
  {
    digitalWrite(1,!digitalRead(1));
    ticks = 0;
    buttonreleased = false;
  }
  if(digitalRead(9) == HIGH && buttonreleased)
  {
    digitalWrite(2,!digitalRead(2));
    ticks = 0;
    buttonreleased = false;
  }
  if(digitalRead(10) == HIGH && buttonreleased)
  {
    digitalWrite(3,!digitalRead(3));
    ticks = 0;
    buttonreleased = false;
  }
  if(digitalRead(7) == LOW && digitalRead(8) == LOW && digitalRead(9) == LOW && digitalRead(10) == LOW)
  {
    buttonreleased = true;
  }
  ticks++;
  delay(1);
}
