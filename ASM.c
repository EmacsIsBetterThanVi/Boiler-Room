int address = 0;
char tokens[8][16];
int token_id = 0;
char *asmFile;
while (file[address] != 0x00) {
  char tokens[8][16] = {"", "", "", "", "", "", "", ""};
  while (file[address] != 0x0a && file[address] != 0x23) {
    asprintf(&tokens[token_id], "%s%c", tokens[token_id], file[address]);
    if (file[address] == 0x20) {
      token_id++;
    }
    if
    address++;
  }
  if (tokens[0] == "LDAB") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x01, stoh(tokens[1]));
  } else if (tokens[0] == "LDAD") {
    asprintf(&asmFile, "%s%c%c%c", asmFile, 0x02, stoh(tokens[1]),
             stoh(tokens[2]));
  } else if (tokens[0] == "LDAI") {
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x03, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "WDAB") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x04, stoh(tokens[1]));
  } else if (tokens[0] == "WDAD") {
    asprintf(&asmFile, "%s%c%c%c", asmFile, 0x05, stoh(tokens[1]),
             stoh(tokens[2]));
  } else if (tokens[0] == "WDAI") {
    asprintf(&asmFile, "%s%c%c%c%c%c", asmFile, 0x06, stoh(tokens[1]),
             stoh(tokens[2]), stoh(tokens[3]), stoh(tokens[4]));
  } else if (tokens[0] == "MARB") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x07, stoh(tokens[1]));
  } else if (tokens[0] == "MARD") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x08, stoh(tokens[1]));
  } else if (tokens[0] == "MARI") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x09, stoh(tokens[1]));
  } else if (tokens[0] == "ARAB") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0a, stoh(tokens[1]));
  } else if (tokens[0] == "ARAD") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0b, stoh(tokens[1]));
  } else if (tokens[0] == "ARAI") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0c, stoh(tokens[1]));
  } else if (tokens[0] == "SRAB") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0d, stoh(tokens[1]));
  } else if (tokens[0] == "SRAD") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0e, stoh(tokens[1]));
  } else if (tokens[0] == "SRAI") {
    asprintf(&asmFile, "%s%c%c", asmFile, 0x0f, stoh(tokens[1]));
  } else if (tokens[0] == "HLT") {
    asprintf(&asmFile, "%s%c", asmFile, 0xFF);
  }
}