/*
 Alterd from  J. Coliz <maniacbug@ymail.com> getign started example
 ¨to chaos by De Dalsmo

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
// OBS BOS BOS SBOSOSOBOSBOSBOSB
RF24 radio(8,10); // OBS OBS OBS BSDO CHANGED DUE TO PWM PINs
// OSBOBSOSOSBOSBO

// some varibles for the chatt
const uint64_t pipes[1] = { 0xF0F0F0F0E1LL};

String SendMess = ""; boolean hasMessageToSend = false;
String RecivedMess = ""; boolean hasRecivedNewMessage = false;

boolean BlinkBlink = false;
int pistol = 2;

// red green blue white
int strip_lenght = 4;
int strip_pins[4] = {5,9,6,3};
int strip_pwm[4] = {0,0,0,0};
int strip_velocity[4] = {0,0,0,0};
int strip_intencity = 255; // 255

int iterations_of_party_left = 0;

float intencity = 0.1; //*255
int fadeIntMode = 0;
int fadeIntModn_n = 4;

// batterymonitor
int powerOnPin = 7;
int powerMonPin = 0;

// holla back
String knicks[4] = {"kaffe","TARDLEDLIFE","TREFASKEBAB","KRANKELFNATT"};
int nKnicks = 4;

void setup(void)
{
  // swithc on the battery
  pinMode(powerOnPin, OUTPUT);
  digitalWrite(powerOnPin, HIGH);
  
  // configure the radio
  Serial.begin(57600);
  while (!Serial) {; /* wait for serial port to connect. Needed for Leonardo only*/}
  printf_begin();
  
  radio.begin(); // Setup and configure rf radio
  radio.setRetries(15,15);// optionally, increase the delay between retries & # of retries
  radio.openReadingPipe(1,pipes[0]); // everygody in the first pipe
  radio.startListening(); // Start listening

  radio.printDetails(); // Dump the configuration of the rf unit for debugging
  printf("\n --- --- Wellcome to chaos! --- ---\n");
  
  // set upp some blinki
  pinMode(strip_pins[0], OUTPUT);
  pinMode(strip_pins[1], OUTPUT);
  pinMode(strip_pins[2], OUTPUT);
  pinMode(strip_pins[3], OUTPUT);
  // set upp initial velocitys
  randomiseVel(12);
  
  // set upp pistol
  pinMode(pistol,OUTPUT);

}

void loop(void)
{
  /////// start chatt porogram code //////////////////
  
  // chek if ther is a message from computer interface
  while(Serial.available()){
    char character = Serial.read();
    delay(20); // lagniva ikedeterminisktisk fixer.
    SendMess.concat(character);
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
    RecivedMess.toLowerCase();
    hasRecivedNewMessage = true;
    // inserttion to react on buss message
    if(RecivedMess=="dalsmo"){
      BlinkBlink = true; 
      SendMess = knicks[random(nKnicks)];
      hasMessageToSend = true; 
    }else if(RecivedMess=="kaffe"){
        setStrip(0,255,0,0);
        delay(10000);
    }
  }
  
  // this is a chatt program, disply a message if we have one
  if (hasRecivedNewMessage){
    Serial.print("Recived: ");
    Serial.println(RecivedMess);
    RecivedMess = ""; hasRecivedNewMessage = false;
  }
  
  /////// End chatt porogram code //////////////////
  
  // set the brightness (always)
  setStripFade(); 
  setFadeForNextIter();
  setFadeIntencity();
  
  // code to run if we have a message and wana show it
  if(BlinkBlink){
    setStrip(0,0,0,0);
    mabyFirePistol();
    // set the brightness (always)
    if(fadeIntMode==0) {
      setStrip(255,0,0,0);
      delay(1000);
      setStrip(0,255,0,0);
      delay(1000);
      setStrip(0,0,255,0);
      delay(1000);
      setStrip(0,0,0,255);
      delay(1000);
    }
    
    // set upp new velocitys
    if(random(2)==1){
      randomiseVel(50);
    }else{
      randomiseVel(12);
    }
    fadeIntMode= random(fadeIntModn_n);
    BlinkBlink = false;
  }
  
  delay(30);
  
  
  
  
  // chek if we shuld swithc of du to low battery
  // if bal balb blabl

}

void firePistol(){
  digitalWrite(pistol, HIGH);
  delay(1000);
  digitalWrite(pistol, LOW); 
}
void mabyFirePistol(){
   if (random(10)<1){
      firePistol();    
    } 
}

void setFadeForNextIter(){
  // change the brightness for next time through the loop:
  for(int i = 0; i<strip_lenght; i++){
    strip_pwm[i] = strip_pwm[i] + strip_velocity[i];
  }
  // reverse the direction of the fading at the ends of the fade:
  for(int i = 0; i<strip_lenght; i++){
    if (strip_pwm[i] < 0) {
      strip_pwm[i] = 0;
      strip_velocity[i] = -strip_velocity[i] ; 
    }else if (strip_pwm[i] > 255){
      strip_pwm[i] = 255;
      strip_velocity[i] = -strip_velocity[i] ; 
    }
  }
}

void setFadeIntencity(){
  
  
  if(fadeIntMode==0){
    intencity = 0.1;
  }
  
  if(fadeIntMode==1){
    intencity = 1;
    if(random(100)==1){
      fadeIntMode= random(fadeIntModn_n);
    }
  }
  
  if(fadeIntMode==2){
   if(intencity<0.055){
     intencity +=0.0005;
   }else if(intencity<0.99){ 
     intencity =intencity*0.3+0.7;
   }else{
     intencity = 0.05;
   } 
   if(intencity>1){
     intencity = 1;
   }
   if(random(200)==1){
      fadeIntMode= random(fadeIntModn_n);
   }
  }
  
  if(fadeIntMode==3){
    if(intencity==1){
      intencity=0.05;
    }else{
      intencity=1;
    }
    if(random(20)==1){
      fadeIntMode= random(fadeIntModn_n);
    }
    
  }
   
  // if party, wub wub 
  

}

void randomiseVel(int v){
    for(int i = 0; i<strip_lenght; i++){
      strip_velocity[i] = random(v);
    }
}

void setStripFade(){
  strip_intencity = (int) (intencity*255);
  setStrip(strip_pwm[0]*strip_intencity/255,strip_pwm[1]*strip_intencity/255,strip_pwm[2]*strip_intencity/255,strip_pwm[3]*strip_intencity/255);
}

void setStrip(int r,int g, int b, int w){
    analogWrite(strip_pins[0], r);
    analogWrite(strip_pins[1], g);
    analogWrite(strip_pins[2], b);
    analogWrite(strip_pins[3], w); 
}


// vim:cin:ai:sts=2 sw=2 ft=cpp
