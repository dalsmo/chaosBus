float batteryfilter = 1023.0;

void chekBattery(){
  int temp = 0;
  temp = analogRead(powerMonPin);
  //Serial.println(temp);
  batteryfilter = batteryfilter*0.9 + (float)temp*0.1;
  
   
  if((batteryfilter)<powerReff){
    digitalWrite(powerOnPin, LOW);// shut down
    Serial.println(batteryfilter); 
  }else{
    digitalWrite(powerOnPin, HIGH);// keep power on
  }
}
