
// holla back
const String knicks[7] = {"kaffe","TLED","HARAM","HALAL","TREFASKEBAB","fantabulous","dalsmo"};
int nKnicks = 7;

void AnalyseMessage(void){
  if(usefullLength(recived)>0){
    if(strcmp(recived,"bombox")==0){
      // svara
      knicks[random(nKnicks)].toCharArray(toSend,32);
      senMessOnChaosBuss();
      ChangeState();
    }
  }
}
  
  
void ChangeState(void){
  fadeIntMode= random(fadeIntModn_n-1)+1;
  // set upp new velocitys
    if(random(2)==1){
      randomiseVel(50);
    }else{
      randomiseVel(12);
    }
}

void updateStateModel(void){
  if(random(1000)==1){
     fadeIntMode=0; 
  }
}
 
  
  
  
  
  
