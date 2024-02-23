#include <ezButton.h> //

ezButton toggleSwitch(0); // switch = 0 create ezButton object that attach to pin 0;

// LEDs for Safety Lights
int led12 = 8; // White (LED1 + LED2)
int led34 = 2; // Red (LED3 + LED4 + Buzzer2)
int led56 = 3; // White (LED5 + LED6)   

// Ultra-Sonic Pins
int trigo = 4;
int echo = 5;

// Pins for Hallway , Electric Box
int ldr1 = 7; // In main house with led11 
int ldr2 = 9;  // Electric box
 
int led11 = 6; // Red LED
int buzzer = 10; // Red LED shorted with Buzzer

int led7 = 11; // White LED
int led8 = 12; // Red LED

int led9 = 13; // White LED (Electric Box)

// Int vales for Ultra Sonic Calculations 
int dura;
int dist;

void setup() {
  Serial.begin(9600);
  pinMode(led12, OUTPUT);
  pinMode(led34, OUTPUT);
  pinMode(led56, OUTPUT);
  pinMode(trigo, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  pinMode(led11, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);

  toggleSwitch.setDebounceTime(50); 

}

void loop() {
  
  int switchState = toggleSwitch.getState(); // Int which takes value of status of switch
  digitalWrite(led11, HIGH); 
  digitalWrite(led9, HIGH);

  if (switchState == HIGH) { // Safety Mode
    Serial.println("Mode 1: Safety Mode");

    digitalWrite(led8, LOW); // RED LED

    // Distance Calculation

    digitalWrite(trigo, HIGH);
    delayMicroseconds(10);  
    digitalWrite(trigo, LOW);

  
    dura = pulseIn(echo, HIGH);
    dist = dura * 0.017;
    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.println(" cm");

    // Checking Distance
    if (dist <= 15) {
      digitalWrite(led12, HIGH); 
      digitalWrite(led34, LOW);
      digitalWrite(led56, HIGH);
      Serial.println("Led12, Led56 are High & Led 34 are Low");
    }
    else if (dist <= 35) {
      digitalWrite(led12, HIGH);
      digitalWrite(led34, LOW);
      digitalWrite(led56, LOW);
      Serial.println("Led12 High & Led 34, led 56 are Low");
    }
    else {
      digitalWrite(led12, LOW);
      digitalWrite(led34, LOW);
      digitalWrite(led56, LOW);
      Serial.println("Led12, Led56 & Led 34 are Low");
    }

     // Checking LDR2 Status
    if (digitalRead(ldr1) == LOW) {
      digitalWrite(buzzer, LOW);
      digitalWrite(led8, LOW); // RED LED 
      digitalWrite(led7, HIGH); // WHITE LED
    }
    else {
      digitalWrite(buzzer, LOW);
      digitalWrite(led8, LOW); // RED LED
      digitalWrite(led7, LOW); // WHITE LED 
   }
    delay(100);
  }
  else {   // Emergency Mode
    Serial.println("Mode 2: Emergency Mode");

      digitalWrite(led12, LOW);
      digitalWrite(led56, LOW);
      digitalWrite(led8, LOW); // RED LED 

    // Distance Calculation

    digitalWrite(trigo, HIGH);
    delayMicroseconds(10);  
    digitalWrite(trigo, LOW);
  
    dura = pulseIn(echo, HIGH);
    dist = dura * 0.017;
    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.println(" cm");

    // Checking Distance 

    if (dist <= 25) {
      digitalWrite(led12, LOW);
      digitalWrite(led34, HIGH); // A Buzzer is shorted to led34
      digitalWrite(led56, LOW);
      Serial.println("Led12, Led56 are Low & Led 34 are High");
    }
    else {
      digitalWrite(led12, LOW);
      digitalWrite(led34, LOW);
      digitalWrite(led56, LOW);

      Serial.println("Led12, Led56 & Led 34 are Low");
    }

  // Checking LDR1 Status

    if (digitalRead(ldr1) == LOW) {
      digitalWrite(led8, HIGH); 
    }
    else {
      digitalWrite(buzzer, LOW);
      digitalWrite(led8, LOW);
   }
    delay(100);
  }

// Checking ldr2 status
       
  if (digitalRead(ldr2) == HIGH) {
    digitalWrite(buzzer, HIGH);
    Serial.println("Electric Box open");
  }
  else {
    digitalWrite(buzzer, LOW);
    Serial.println("Electric Box close");
  }
  delay(100);
}