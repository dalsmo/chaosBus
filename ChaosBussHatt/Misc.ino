
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
