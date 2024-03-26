int address = 0;
char tokens[8][16];
int token_id=0;
char * asmFile;
while (file[address] != 0x00) {
  char tokens[8][16]={"", "", "", "", "", "", "", ""};
  while (file[address] != 0x0a && file[address] != 0x23) {
    asprintf(&tokens[token_id], "%s%c", tokens[token_id], file[address]);
    if(file[address] == 0x20) {
      token_id++;
    }
    address++;
  }
  if(tokens[0]=="LDAB"){
    asprintf(&asmFile, "%s%c%c", asmFile, 0x01, stoh(tokens[1]));
  } else if(tokens[0]=="LDAD"){
    asprintf(&asmFile, "%s%c%c%c", asmFile, 0x02, stoh(tokens[1]), stoh(tokens[2]));
  } else if(tokens[0]=="LDAI")){
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x03, stoh(tokens[1]), stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if(tokens[0]=="WDAB"){
      asprintf(&asmFile, "%s%c%c", asmFile, 0x04, stoh(tokens[1]));
    } else if(tokens[0]=="WDAD"){
      asprintf(&asmFile, "%s%c%c%c", asmFile, 0x05, stoh(tokens[1]), stoh(tokens[2]));
    } else if(tokens[0]=="WDAI")){
      asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x06, stoh(tokens[1]), stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
    }
}