/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(57600);
  pinMode(13, OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("--------------");
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("13");
  delay(10000);
  digitalWrite(13, LOW);
  digitalWrite(9, HIGH);
  Serial.println("9");
  delay(10000);
  digitalWrite(9, LOW);
  digitalWrite(6, HIGH);
  Serial.println("6");
  delay(10000);
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  Serial.println("5");
  delay(10000);
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  Serial.println("4");
  delay(10000);
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
  Serial.println("3");
  delay(10000);
  digitalWrite(3, LOW); 
  
}
