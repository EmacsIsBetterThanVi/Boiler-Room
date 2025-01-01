/*REGISTERS:
%0:   FLAGS
%ED:  Acum Backup FIRST BYTE
%EE:  Acum Backup SECOND BYTE
%EF:  Acum Backup THIRD BYTE
%F0:  Acum Backup FORTH BYTE
%F1:  Acum FIRST BYTE
%F2:  Acum SECOND BYTE
%F3:  Acum THIRD BYTE
%F4:  Acum FORTH BYTE
%F5:  SP FIRST BYTE
%F6:  SP SECOND BYTE
%F7:  SP THIRD BYTE
%F8:  SP FORTH BYTE
%F9:  PC FIRST BYTE
%FA:  PC SECOND BYTE
%FB:  PC THIRD BYTE
%FC:  PC FORTH BYTE
%FD:  FIRST BYTE
%FE:  SECOND BYTE
%FF:  THIRD BYTE
*/
int address = 0;
char tokens[8][16];
int token_id = 0;
char *asmFile;
char header[512] = "";
int binaddress = 0;
int tmp[8];
while (file[address] != 0x00) {
  char tokens[8][16] = {"", "", "", "", "", "", "", ""};
  while (file[address] != 0x0a && file[address] != 0x23) {
    asprintf(&tokens[token_id], "%s%c", tokens[token_id], file[address]);
    if (file[address] == 0x20) {
      if (tokens[token_id] == "%A") {
        binaddress = binaddress + 5;
        tmp[4] = binaddress + 1 + token_id;
        tmp[3] = tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 256);
        tmp[4] = tmp[4] / 256;
        tmp[2] = tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 256);
        tmp[4] = tmp[4] / 256;
        tmp[1] = tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 16);
        tmp[4] = tmp[4] / 16;
        tmp[0] = tmp[4];
        asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x04, tmp[0], tmp[1],
                 tmp[2], tmp[3]);
      } else if (tokens[token_id][0] == '%') {
        tokens[token_id][0] = tokens[token_id][1];
        tokens[token_id][1] = tokens[token_id][2];
        tokens[token_id][2] = tokens[token_id][3];
        if(stoh(tokens[token_id]) > 255){
          printf("ERROR: INVALID TOKEN: %%s\n", tokens[token_id]);
          return 5;
        }
        binaddress = binaddress + 9;
        tmp[4] = binaddress + 1 + token_id;
        tmp[3] = tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 256);
        tmp[4] = tmp[4] / 256;
        tmp[2] = tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 256);
        tmp[4] = tmp[4] / 256;
        tmp[1] = tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 16);
        tmp[4] = tmp[4] / 16;
        tmp[0] = tmp[4];
        asprintf(&asmFile, "%s%c%c%c%c%c%c%c%c%c", asmFile, 0x08, 0xED, 0x10, 0x0C,
                 stoh(tokens[token_id]), tmp[0], tmp[1], tmp[2], tmp[3]);
      } else {
        printf("ERROR: UNKNOWN TOKEN: %s\n", tokens[token_id]);
        return 2;
      }
      token_id++;
    }
    address++;
  }
  if (tokens[0] == "LDAB") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x01, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "LDAD") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x02, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "LDAI") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x03, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "WDAB") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x04, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "WDAD") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x05, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "WDAI") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x06, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "MARB") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x07, stoh(tokens[1]));
  } else if (tokens[0] == "MARD") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x08, stoh(tokens[1]));
  } else if (tokens[0] == "MARI") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x09, stoh(tokens[1]));
  } else if (tokens[0] == "ARAB") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0a, stoh(tokens[1]));
  } else if (tokens[0] == "ARAD") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0b, stoh(tokens[1]));
  } else if (tokens[0] == "ARAI") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0c, stoh(tokens[1]));
  } else if (tokens[0] == "SRAB") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0d, stoh(tokens[1]));
  } else if (tokens[0] == "SRAD") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0e, stoh(tokens[1]));
  } else if (tokens[0] == "SRAI") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0f, stoh(tokens[1]));
  } else if (tokens[0] == "INB") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x11, stoh(tokens[1]));
  } else if (tokens[0] == "IND") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x12, stoh(tokens[1]));
  } else if (tokens[0] == "INI") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x13, stoh(tokens[1]));
  } else if (tokens[0] == "OUTB") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x14, stoh(tokens[1]));
  } else if (tokens[0] == "OUTD") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x15, stoh(tokens[1]));
  } else if (tokens[0] == "OUTI") {
    binaddress += 2;
    asprintf(&asmFile, "%s%c%c", asmFile, 0x16, stoh(tokens[1]));
  } else if (tokens[0] == "HLT") {
    binaddress += 1;
    asprintf(&asmFile, "%s%c", asmFile, 0xFF);
  } else if (tokens[0] == "CLA") {
    binaddress += 1;
    asprintf(&asmFile, "%s%c", asmFile, 0x10);
  } else if(tokens[0][0] == '$'){
    if(tokens[0] == "$inject"){
      while(true){
        if(file[address] == 0x00){
          printf("ERROR: INJECT INSTUCTION DOES NOT TERMINATE\n");
          return 4;
        }
        if(file[address] == '#') break;
        tokens[1][0]=file[address];
        address++;
        tokens[1][1]=file[address];
        tokens[1][2]=0x00;
        address++;
        asprintf(&asmFile, "%s%c", asmFile, stoh(tokens[1]));
      }
    } else if(tokens[0] == "$require"){
      asprintf(&header, "%s;port %s %s;?open %s", header, tokens[1], tokens[2], tokens[2]);
    } else if(tokens[0] == "$port"){
      asprintf(&header, "%s;port %s %s", header, tokens[1], tokens[2]);
    } else if(tokens[0] == "$isopen"){
      asprintf(&header, "%s;?open %s", header, tokens[1]);
    } else if(tokens[0] == "$init") {
      asprintf(&header, "%s;init %s %s", header, tokens[1], tokens[2]);
    }else if(tokens[0][1] != '#'){
      printf("ERROR: UNKNOWN ASSEMBLER INSTUCTION: %s\n", tokens[0]);
      return 3;
    }
  }else {
    printf("ERROR: UNKNOWN INSTRUCTION: %s\n", tokens[0]);
    return 1;
  }
}