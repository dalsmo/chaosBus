/*
 Alterd from  J. Coliz <maniacbug@ymail.com> getign started example
 ¨to chaos by De Dalsmo

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(9,10);

// some varibles for the chatt
const uint64_t pipes[1] = { 0xF0F0F0F0E1LL};
String SendMess = ""; boolean hasMessageToSend = false;
String RecivedMess = ""; boolean hasRecivedNewMessage = false;

// stof to read teh buttons
int buttPin = 0;
boolean buttPress = false;

void setup(void)
{
  Serial.begin(57600);
  while (!Serial) {; /* wait for serial port to connect. Needed for Leonardo only*/}
  printf_begin();
  
  radio.begin(); // Setup and configure rf radio
  radio.setRetries(15,15);// optionally, increase the delay between retries & # of retries
  radio.openReadingPipe(1,pipes[0]); // everygody in the first pipe
  radio.startListening(); // Start listening

  radio.printDetails(); // Dump the configuration of the rf unit for debugging
  printf("\n --- --- Wellcome to chaos! --- ---\n");
}

void loop(void)
{
  
  // chek if ther is a message from computer interface
  while(Serial.available()){
    char character = Serial.read();
    delay(20); // lagniva ikedeterminisktisk fixer.
    SendMess.concat(character);
    hasMessageToSend = true;  
  }
  
  // chek if button has been released
  if (analogRead(buttPin)>1020){
    buttPress = false;
  }
  
  // chek if a button has been pressed, and set a message
  if (!buttPress && (analogRead(buttPin)<1020)){
    buttPress = true;
    Serial.println("button pressed");
    SendMess = "TLED";
    hasMessageToSend = true;
  }
  
  // if we have a message in the buffer we send it
  if (hasMessageToSend){   
    radio.openWritingPipe(pipes[0]);  radio.stopListening(); // and, stop listening open pipes, so we can talk. 
    
    int k = SendMess.length()+1; char temp[k];
    SendMess.toCharArray(temp, k) ;
    bool ok = radio.write( &temp, sizeof(char)*k);
    
    Serial.print("Sending: "); Serial.print(SendMess);
    if (ok){printf("\n");}else{printf("   (failed)\n");}

    SendMess = ""; hasMessageToSend = false;
    radio.startListening(); radio.openReadingPipe(1,pipes[0]);
  }
  
  // If there is data to read from ChaosBuss
  while (radio.available()){   
    char recived[40];
    radio.read( &recived, sizeof(char)*40);
    RecivedMess.concat(recived);
    hasRecivedNewMessage = true; 
  }
  
  // this is a chatt program, disply a message if we have one
  if (hasRecivedNewMessage){
    Serial.print("Recived: ");
    Serial.println(RecivedMess);
    RecivedMess = ""; hasRecivedNewMessage = false;
  }
  
  
  

}
// vim:cin:ai:sts=2 sw=2 ft=cpp
