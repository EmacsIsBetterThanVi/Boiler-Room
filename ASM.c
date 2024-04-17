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
int binaddress = 0;
int tmp[8];
while (file[address] != 0x00) {
  char tokens[8][16] = {"", "", "", "", "", "", "", ""};
  while (file[address] != 0x0a && file[address] != 0x23) {
    asprintf(&tokens[token_id], "%s%c", tokens[token_id], file[address]);
    if (file[address] == 0x20) {
      if (tokens[token_id] == "%A" ){
        binaddress = binaddress + 5;
        tmp[3]=binadress % 256;
        tmp[4]=binadress - (binadress % 256);
        tmp[4]=tmp[4]/256;
        tmp[2]=tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 256);
        tmp[4] = tmp[4] / 256;
        tmp[1] = tmp[4] % 256;
        tmp[4] = tmp[4] - (tmp[4] % 16);
        tmp[4] = tmp[4] / 16;
        tmp[0] = tmp[4];
        asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x04, );
      } else if (tokens[token_id][0] == '%') {
        binaddress = binaddress + 5;
        asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x08, 0xED, 0x10, 0x0C, stoh(tokens[token_id]));
      }
      token_id++;
    }
    address++;
  }
  if (tokens[0] == "LDAB") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x01, stoh(tokens[1]),stoh(tokens[2]),stoh(tokens[3]),stoh(tokens[4]));
  } else if (tokens[0] == "LDAD") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x02, stoh(tokens[1]),stoh(tokens[2]),stoh(tokens[3]),stoh(tokens[4]));
  } else if (tokens[0] == "LDAI") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x03, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "WDAB") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x04, stoh(tokens[1]),stoh(tokens[2]),stoh(tokens[3]),stoh(tokens[4]));
  } else if (tokens[0] == "WDAD") {
    binaddress += 5;
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x05, stoh(tokens[1]),stoh(tokens[2]),stoh(tokens[3]),stoh(tokens[4]));
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
  } else if (tokens[0] == "HLT") {
    binaddress += 1;
    asprintf(&asmFile, "%s%c", asmFile, 0xFF);
  } else if (tokens[0] == "CLA") {
    binaddress += 1;
    asprintf(&asmFile, "%s%c", asmFile, 0x10);
  }
}