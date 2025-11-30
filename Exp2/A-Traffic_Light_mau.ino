//Four Way Traffic Ligh

#include <TM1637Display.h>

#define CLK A0
#define DIO A1
TM1637Display display(CLK, DIO);



int RED[]    = {2, 5, 8, 11};
int YELLOW[] = {3, 6, 9, 12};
int GREEN[]  = {4, 7, 10, 13};
#define NUM_DIRECTIONS 4


void setup() {
  for (int i = 0; i < NUM_DIRECTIONS; i++) {
    pinMode(RED[i], OUTPUT);
    pinMode(YELLOW[i], OUTPUT);
    pinMode(GREEN[i], OUTPUT);
  }
 
  display.setBrightness(0x0f);  
  display.showNumberDec(0, true);
}


void loop() {
  for (int i = 0; i < NUM_DIRECTIONS; i++) {
    for (int j = 0; j < NUM_DIRECTIONS; j++) {
      digitalWrite(RED[j], HIGH);
      digitalWrite(YELLOW[j], LOW);
      digitalWrite(GREEN[j], LOW);
    }
   
    digitalWrite(RED[i], LOW);
    digitalWrite(GREEN[i], HIGH);
    countdownTimer(10);  
  
    digitalWrite(GREEN[i], LOW);
    digitalWrite(YELLOW[i], HIGH);
    countdownTimer(3);  
    
    digitalWrite(YELLOW[i], LOW);
    digitalWrite(RED[i], HIGH);
    delay(500);
  }
}

void countdownTimer(int totalSeconds) {
  for (int sec = totalSeconds; sec >= 0; sec--) {
    int minutes = sec / 60;
    int seconds = sec % 60;
    int displayTime = (minutes * 100) + seconds;
    display.showNumberDecEx(displayTime, 0b01000000, true);  
    delay(1000);
  }
}
