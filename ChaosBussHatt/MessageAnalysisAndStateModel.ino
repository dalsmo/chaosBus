
void AnalyseMessage(void){
  if(usefullLength(recived)>0){
    if(strcmp(recived,"kaffe")==0){
      firePistol();
    }else if(strcmp(recived,"dalsmo")==0){
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
 
  
  
  
  
  
