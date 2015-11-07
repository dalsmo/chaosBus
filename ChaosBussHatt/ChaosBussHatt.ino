/*
 Alterd from  J. Coliz <maniacbug@ymail.com> getign started example
 ¨to chaos by De Dalsmo

*/

// pistol pin
int pistol = 2;

// red green blue white
int strip_lenght = 4;
int strip_pins[4] = {5,9,6,3};
int strip_position[4] = {0,0,0,0};
int strip_velocity[4] = {0,0,0,0};

float intencity = 0.1; //*255 
int fadeIntMode = 0;
int fadeIntModn_n = 4;

// batterymonitor
int powerOnPin = 7;
int powerMonPin = 0;
int powerReff = 605;

// holla back
const String knicks[7] = {"kaffe","TLED","HARAM","HALAL","TREFASKEBAB","bombox","fantabulous"};
int nKnicks = 7;

int radioRestatFallback = 0;

void setup(void)
{
  // swithc on the battery
  pinMode(powerOnPin, OUTPUT);
  digitalWrite(powerOnPin, HIGH);
  
  // start the radio
  startRadio();
  
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
  /////// chek battery ////////////////
  chekBattery();
  
  /////// start chatt porogram code //////////////////
  checkMessageFromComputeromputer();
  senMessOnChaosBuss();
  readMessOnChaosBuss();
  AnalyseMessage(); // important!!!!!!!!!!!!!!!!!!!!!!!!!!
  printMessToComputer(); // which also removes the message
  
  /////// blink blink code //////////////////
  
  // set the brightness (always)
  uppdatePossitions();
  setStripLEDs();
  updateFadeIntencity();
  
  updateStateModel();
  
  
  ////////////  radio restar fallack /////////
  if(radioRestatFallback>=10000){
    startRadio();
    radioRestatFallback=0;
  }radioRestatFallback++;
  
  //////////// just chill ////////////////////
  
  
 delay(30);
}












// vim:cin:ai:sts=2 sw=2 ft=cpp
