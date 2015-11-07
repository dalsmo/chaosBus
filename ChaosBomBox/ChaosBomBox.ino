
// red green blue white {5,9,6,3};
// green red blue white {9,5,6,3};
int strip_lenght = 4;
int strip_pins[4] = {9,5,6,3};
int strip_position[4] = {0,0,0,0};
int strip_velocity[4] = {0,0,0,0};

float intencity = 0.1; //*255 
int fadeIntMode = 0;
int fadeIntModn_n = 4;

// batterymonitor
int powerOnPin = 2;
int powerMonPin = 7;
int powerReff = 608;

// the setup function runs once when you press reset or power the board
void setup() {
  
  // hold power on
  pinMode(powerOnPin, OUTPUT);
  digitalWrite(powerOnPin, HIGH);
  
  
  
  // serial stuff
  Serial.begin(57600);
  
  // fix radio
  startRadio();
  
  // set upp some blinki
  pinMode(strip_pins[0], OUTPUT);
  pinMode(strip_pins[1], OUTPUT);
  pinMode(strip_pins[2], OUTPUT);
  pinMode(strip_pins[3], OUTPUT);
  // set upp initial velocitys
  randomiseVel(12);

}

// the loop function runs over and over again forever
void loop() {
  chekBattery();
  
  checkMessageFromComputeromputer();
  senMessOnChaosBuss();
  readMessOnChaosBuss();
  AnalyseMessage(); // important!!!!!!!!!!!!!!!!!!!!!!!!!!
  printMessToComputer();
  
  int temp = 0;
  temp = analogRead(6);
  if(temp<=1){
    intencity = 0;
  }else if(temp <1020){
    intencity = (float)temp/1023;  
  }else{
    updateFadeIntencity();
  }
  //
  uppdatePossitions();
  setStripLEDs();
  
  updateStateModel();
  
  // just chill
 delay(30);
  
}
