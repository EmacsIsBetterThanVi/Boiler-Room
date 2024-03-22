/*REGISTERS:
R0:     FLAGS
R241:   Acum FIRST BYTE
R242:   Acum SECOND BYTE
R243:   Acum THIRD BYTE
R244:   Acum FORTH BYTE
R245:   SP FIRST BYTE
R246:   SP SECOND BYTE
R247:   SP THIRD BYTE
R248:   SP FORTH BYTE
R249:   PC FIRST BYTE
R250:   PC SECOND BYTE
R251:   PC THIRD BYTE
R252:   PC FORTH BYTE
R253:   FIRST BYTE
R254:   SECOND BYTE
R255:   THIRD BYTE
*/
int PC;
int tmp;
while (true) {
  PC = ((REGISTERS[249] * 16 + REGISTERS[250]) * 16 + REGISTERS[251]) * 16 + REGISTERS[252];
  switch (file[PC]) {
  case 0x01: // LDAI
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 16 + REGISTERS[254]) * 16 + REGISTERS[255]) +
          file[PC];
    REGISTERS[241] = file[tmp];
    REGISTERS[242] = file[tmp + 1];
    REGISTERS[243] = file[tmp + 2];
    REGISTERS[244] = file[tmp + 3];
    break;
  case 0x02: // LDAD
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 16 + REGISTERS[254]) * 16 + REGISTERS[255]) +
          file[PC];
    REGISTERS[241] = 0;
    REGISTERS[242] = 0;
    REGISTERS[243] = file[tmp];
    REGISTERS[244] = file[tmp + 1];
    break;
  case 0x03: //LDAB
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 16 + REGISTERS[254]) * 16 + REGISTERS[255]) +
          file[PC];
    REGISTERS[241] = 0;
    REGISTERS[242] = 0;
    REGISTERS[243] = 0;
    REGISTERS[244] = file[tmp];
    break;
    case 0x04: // WDAI
      PC++;
      REGISTERS[253] = file[PC];
      PC++;
      REGISTERS[254] = file[PC];
      PC++;
      REGISTERS[255] = file[PC];
      PC++;
      tmp = ((REGISTERS[253] * 16 + REGISTERS[254]) * 16 + REGISTERS[255]) +
            file[PC];
      file[tmp]=REGISTERS[241];
      file[tmp+1]=REGISTERS[242];
      file[tmp+2]=REGISTERS[243];
      file[tmp+3]=REGISTERS[244];
      break;
    case 0x05: // WDAD
      PC++;
      REGISTERS[253] = file[PC];
      PC++;
      REGISTERS[254] = file[PC];
      PC++;
      REGISTERS[255] = file[PC];
      PC++;
      tmp = ((REGISTERS[253] * 16 + REGISTERS[254]) * 16 + REGISTERS[255]) +
        file[PC];
      file[tmp]=REGISTERS[243];
      file[tmp+1]=REGISTERS[244];
      break;
    case 0x06: // WDAB
      PC++;
      REGISTERS[253] = file[PC];
      PC++;
      REGISTERS[254] = file[PC];
      PC++;
      REGISTERS[255] = file[PC];
      PC++;
      tmp = ((REGISTERS[253] * 16 + REGISTERS[254]) * 16 + REGISTERS[255]) +
        file[PC];
      file[tmp]=REGISTERS[244];
      break;
    case 0x07: // MARB
      PC++;
      REGISTERS[file[PC]]= REGISTERS[244];
      break;
    case 0x08: // MARD
      PC++;
      REGISTERS[file[PC]]= REGISTERS[243];
      REGISTERS[file[PC]+1]= REGISTERS[244];
      break;
    case 0x09: // MARI
      PC++;
      REGISTERS[file[PC]]= REGISTERS[241];
      REGISTERS[file[PC]+1]= REGISTERS[242];
      REGISTERS[file[PC]+2]= REGISTERS[243];
      REGISTERS[file[PC]+3]= REGISTERS[244];
      break;
    case 0x0a: // ARAB
      PC++;
      tmp = ((REGISTERS[241] * 16 + REGISTERS[242]) * 16 + REGISTERS[243]) * 16 + REGISTERS[244];
      tmp+=REGISTERS[file[PC]];
      REGISTERS[244] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[243] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[242] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[241] = tmp;
      break;
    case 0x0b: // ARAD
      PC++;
      tmp = ((REGISTERS[241] * 16 + REGISTERS[242]) * 16 + REGISTERS[243]) * 16 + REGISTERS[244];
      tmp += REGISTERS[file[PC]] * 16 + REGISTERS[file[PC]+1]; 
      REGISTERS[244] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[243] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[242] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[241] = tmp;
      break;
    case 0x0c: // ARAI
      PC++;
      tmp = ((REGISTERS[241] * 16 + REGISTERS[242]) * 16 + REGISTERS[243]) * 16 + REGISTERS[244];
      tmp += ((REGISTERS[file[PC]] * 16 + REGISTERS[file[PC]+1]) * 16 + REGISTERS[file[PC]+2]) * 16 + REGISTERS[file[PC]+3];
      REGISTERS[244] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[243] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[242] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[241] = tmp;
      break;
    case 0x0d: // SRAB
      PC++;
      tmp = ((REGISTERS[241] * 16 + REGISTERS[242]) * 16 + REGISTERS[243]) * 16 + REGISTERS[244];
      tmp -= REGISTERS[file[PC]];
      REGISTERS[244] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[243] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[242] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[241] = tmp;
      break;
    case 0x0e: // SRAD
      PC++;
      tmp = ((REGISTERS[241] * 16 + REGISTERS[242]) * 16 + REGISTERS[243]) * 16 + REGISTERS[244];
      tmp -= REGISTERS[file[PC]] * 16 + REGISTERS[file[PC] + 1]; 
      REGISTERS[244] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[243] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[242] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[241] = tmp;
      break;
    case 0x0f: // SRAI
      PC++;
      tmp = ((REGISTERS[241] * 16 + REGISTERS[242]) * 16 + REGISTERS[243]) * 16 + REGISTERS[244];
      tmp -= ((REGISTERS[file[PC]] * 16 + REGISTERS[file[PC] + 1]) * 16 + REGISTERS[file[PC] + 2]) * 16 + REGISTERS[file[PC] + 3];
      REGISTERS[244] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[243] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[242] = tmp % 16;
      tmp -= tmp % 16;
      tmp = tmp / 16;
      REGISTERS[241] = tmp;
      break;
  }
  PC++;
  if (file[PC] == 0x00) { // HLT
    break;
  }
  REGISTERS[252] = PC % 16;
  PC -= PC % 16;
  PC = PC / 16;
  REGISTERS[251] = PC % 16;
  PC -= PC % 16;
  PC = PC / 16;
  REGISTERS[250] = PC % 16;
  PC -= PC % 16;
  PC = PC / 16;
  REGISTERS[249] = PC;
}