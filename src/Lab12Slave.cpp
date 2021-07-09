/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/evanh/OneDrive/Desktop/CTD/InternetOfThings/Lab12Slave/src/Lab12Slave.ino"
void takeAction(uint8_t state);
void setup();
void loop();
#line 1 "c:/Users/evanh/OneDrive/Desktop/CTD/InternetOfThings/Lab12Slave/src/Lab12Slave.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);


volatile bool cs = false;


void takeAction(uint8_t state) {
  if (state) {
    cs = true;

  }
}

void setup() {
  
  //init pin modes
  pinMode(A5, OUTPUT);
  pinMode(A1, INPUT);
  
  //serial
  Serial.begin(9600);
    
  //set up SPI
  SPI1.begin(SPI_MODE_SLAVE, D6);
  SPI1.setClockSpeed(1,MHZ);
  SPI1.setBitOrder(MSBFIRST);
  SPI1.setDataMode(SPI_MODE0);
  SPI1.onSelect(takeAction);
  
}

void loop() {
  char rx[1];
  char tx[1];
  

  if (cs) 
  {
    cs = false;

    tx[0] = '*';
    SPI1.transfer(tx,rx,1,NULL);

    Serial.println(rx);
    if (rx[0] == '1') 
    {
      digitalWrite(A5,HIGH);
    }
    else if (rx[0] == '0') 
    {
      digitalWrite(A5,LOW);
    }
    else if (rx[0] == '?') 
    {
      if (digitalRead(A1) == HIGH){
        tx[0] = 'D';
      }
      else {
        tx[0] = 'U';
      }
      SPI1.transfer(tx,rx,1,NULL);

    }

  }
}
