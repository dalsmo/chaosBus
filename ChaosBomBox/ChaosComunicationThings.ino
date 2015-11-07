
// includes
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"


// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(8,10);
const uint64_t pipes[1] = { 0xF0F0F0F0E1LL};
char toSend[32] = {'\0'};
char recived[32] = {'\0'};

void startRadio(void){
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

void checkMessageFromComputeromputer(void){
  // chek if ther is a message from computer interface
  int i =0;
  while(Serial.available() || i>31){
    toSend[i]  = Serial.read();
    delay(20); // lagniva ikedeterminisktisk fixer.
    i++;
  }toSend[i] = '\0';
}

void printMessToComputer(void){
  // this is a chatt program, disply a message if we have one
  if (usefullLength(recived)>0){
    Serial.print("Recived: ");
    Serial.println(recived);
    recived[0] = '\0';
  }
}

void senMessOnChaosBuss(void){
  // if we have a message in the buffer we send it
  if (usefullLength(toSend)>0){   
    radio.openWritingPipe(pipes[0]);  radio.stopListening(); // and, stop listening open pipes, so we can talk. 
    
    bool ok = radio.write( &toSend, sizeof(char)*usefullLength(toSend));
    
    Serial.print("Sending: "); Serial.print(toSend);
    if (ok){printf("\n");}else{printf("   (failed)\n");}

    toSend[0] = '\0';
    radio.startListening(); radio.openReadingPipe(1,pipes[0]); 
  }
}

void readMessOnChaosBuss(void){
  // If there is data to read from ChaosBuss
  while (radio.available()){   
    radio.read( &recived, sizeof(char)*32);
  }
}



////////////////////////////////////// just some usefull funcitons
int usefullLength(char *charArry){
  int i=0;
  for(i=0;i<32; i++){
    if(charArry[i]=='\0'){
      return i;
    }
  }
  return i;
}

