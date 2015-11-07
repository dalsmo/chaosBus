
void randomiseVel(int v){
    for(int i = 0; i<strip_lenght; i++){
      strip_velocity[i] = random(v);
    }
}

void uppdatePossitions(){
  // change the brightness for next time through the loop:
  for(int i = 0; i<strip_lenght; i++){
    strip_position[i] = strip_position[i] + strip_velocity[i];
  }
  // reverse the direction of the fading at the ends of the fade:
  for(int i = 0; i<strip_lenght; i++){
    if (strip_position[i] < 0) {
      strip_position[i] = 0;
      strip_velocity[i] = -strip_velocity[i] ; 
    }else if (strip_position[i] > 255){
      strip_position[i] = 255;
      strip_velocity[i] = -strip_velocity[i] ; 
    }
  }
}

void updateFadeIntencity(){ 
  if(fadeIntMode==0){
    intencity = 0.1;
  }
  
  if(fadeIntMode==1){
    intencity = 1;
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
  }
  
  if(fadeIntMode==3){
    if(intencity==1){
      intencity=0.05;
    }else{
      intencity=1;
    }   
  }
}

void setStripLEDs(){
  int temp = (int) (intencity*255);
  setStrip(strip_position[0]*temp/255,strip_position[1]*temp/255,strip_position[2]*temp/255,strip_position[3]*temp/255);
}

void setStrip(int r,int g, int b, int w){
    analogWrite(strip_pins[0], r);
    analogWrite(strip_pins[1], g);
    analogWrite(strip_pins[2], b);
    analogWrite(strip_pins[3], w); 
}
