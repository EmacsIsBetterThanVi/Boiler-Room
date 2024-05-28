/*
INTERUPTS:
1: CTRL+C
INTERUPT CONFIGURATION
CalledInterupts containes weather an interupt is active
*/
char INTERUPTS[10];
bool interrupts_enabled = true;
bool CalledInterupts[256];
int InteruptJumps[256];
void FillInterupts(char interupt){
  for(int i = 0; i < 10; i++){
    if(INTERUPTS[i] == 0){
      INTERUPTS[i] = interupt;
      return;
    }
  }
}
void ShiftInterupts(int start){
  if(start==10){
    for(int i = 0; i < 10; i++){
      INTERUPTS[i] = 0;
    }
    return;
  }
  if(start<0 || start>8) start=0;
  for(int i = start; i < 10; i++){
    INTERUPTS[i] = INTERUPTS[i+1];
  }
}
signed char CheckInterupt(char Interupt){
  if(!CalledInterupts[Interupt]){
    return -2;
  }
  for(int i = 0; i < 10; i++){
    if(INTERUPTS[i] == Interupt){
      return i;
    }
  }
  return -1;
}
void RemoveInterupt(char Interupt){
  signed char CI = CheckInterupt(Interupt);
  if(CI < 0){
    return;
  }
  ShiftInterupts(CI);
}
void CTRL_C_pressed(int sig){
  if(CalledInterupts[0]){
  FillInterupts(1);
  } else exit(0);
}
void RegisterInterupt(char Interupt, int Address){
  CalledInterupts[Interupt]=false;
  InteruptJumps[Interupt]=Address;
}
void UnregisterInterupt(char Interupt){
  CalledInterupts[Interupt]=false;
  InteruptJumps[Interupt]=0;
}