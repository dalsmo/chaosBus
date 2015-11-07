float batteryfilter = 1023.0;

void chekBattery(){
  int temp = 0;
  temp = analogRead(powerMonPin);
  //Serial.println(temp);
  batteryfilter = batteryfilter*0.8 + (float)temp*0.2;
  
   
  if((batteryfilter)<powerReff){
    digitalWrite(powerOnPin, LOW);// shut down
    Serial.println(batteryfilter); 
  }else{
    digitalWrite(powerOnPin, HIGH);// keep power on
  }
}
