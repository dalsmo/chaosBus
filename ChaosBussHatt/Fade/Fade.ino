/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int nothing = 4;

  // red green blue white
int strip_lenght = 4;
int strip_pins[4] = {5,9,6,3};
int strip_pwm[4] = {0,0,0,0};
int strip_velocity[4] = {0,0,0,0};
int strip_max = 255;


// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(strip_pins[0], OUTPUT);
  pinMode(strip_pins[1], OUTPUT);
  pinMode(strip_pins[2], OUTPUT);
  pinMode(strip_pins[3], OUTPUT);
  
  // set upp initial velocitys
  for(int i = 0; i<strip_lenght; i++){
    strip_velocity[i] = random(12);
  }
  
} 

// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness
  for(int i = 0; i<strip_lenght; i++){
    analogWrite(strip_pins[i], strip_pwm[i]);
  }

  // change the brightness for next time through the loop:
  for(int i = 0; i<strip_lenght; i++){
    strip_pwm[i] = strip_pwm[i] + strip_velocity[i];
  }
  // reverse the direction of the fading at the ends of the fade:
  for(int i = 0; i<strip_lenght; i++){
    if (strip_pwm[i] < 0) {
      strip_pwm[i] = 0;
      strip_velocity[i] = -strip_velocity[i] ; 
    }else if (strip_pwm[i] > strip_max){
      strip_pwm[i] = strip_max;
      strip_velocity[i] = -strip_velocity[i] ; 
    }
  }
  
  
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}

