int address = 0;
char tokens[8][16];
int token_id=0;
char * asmFile;
while (file[address] != 0x00) {
  tokens={"", "", "", "", "", "", "", ""};
  while (file[address] != 0x0a && file[address] != 0x23) {
    token[token_id]+=file[address];
    if(file[address] == 0x20) {
      token_id++;
    }
    address++;
  }
}