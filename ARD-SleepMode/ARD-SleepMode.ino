/*
 * Arduino Sleep mode
 *  wake up using attachInterrupt pin 2(0) or 3(1)
 *  by Bavensky [CMMC]
 */
 
#include <avr/sleep.h>
#define wakePin   3     // pin used for waking up
#define sleepPin  4     // pin used for sleep mode
#define LED1      12    // pin used for wake up indicator light
#define LED2      13    // pin used for sleep mode indicator light

void wakeUpNow()  {
  Serial.println("Wake up");
  digitalWrite(LED2, 0);
  delay(1000);
}

void sleepNow() {   // here we put the arduino to sleep
  /* 
     The 5 different modes are:
         SLEEP_MODE_IDLE         -the least power savings
         SLEEP_MODE_ADC
         SLEEP_MODE_PWR_SAVE
         SLEEP_MODE_STANDBY
         SLEEP_MODE_PWR_DOWN     -the most power savings
     For now, we want as much power savings as possible, so we
     choose the according
     sleep mode: SLEEP_MODE_PWR_DOWN
  */
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
  sleep_enable();          
  
  attachInterrupt(1, wakeUpNow, LOW); // use interrupt 1 (pin 3), wakeUpNow when pin 3 gets LOW
  sleep_mode();   
    
  // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
  sleep_disable();         // disable sleep...
  detachInterrupt(1);      // disables interrupt 1 on pin 3
}

void setup()  {
  pinMode(sleepPin, INPUT_PULLUP);
  pinMode(wakePin, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(1, wakeUpNow, LOW); // use interrupt 1 (pin 3)
}

void loop() {
  Serial.println("MAin...");
  digitalWrite(LED1, 1);
  delay(1000);
  digitalWrite(LED1, 0);
  delay(1000);

  if (digitalRead(sleepPin) == 0) {
    Serial.println("sleep mode");
    digitalWrite(LED2, 1);
    delay(1000);
    sleepNow();
  }
}
