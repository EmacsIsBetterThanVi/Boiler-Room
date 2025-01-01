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
  int indentifier;
  int SP = ((REGISTERS[245] * 256 + REGISTERS[246]) * 256 + REGISTERS[247]) * 256 + REGISTERS[248];
  PC = ((REGISTERS[249] * 256 + REGISTERS[250]) * 256 + REGISTERS[251]) * 256 + REGISTERS[252];
  switch (file[PC]) {
  case 0x03: // LDAI
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 256 + REGISTERS[254]) * 256 + REGISTERS[255]) +
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
    tmp = ((REGISTERS[253] * 256 + REGISTERS[254]) * 256 + REGISTERS[255]) +
          file[PC];
    REGISTERS[241] = 0;
    REGISTERS[242] = 0;
    REGISTERS[243] = file[tmp];
    REGISTERS[244] = file[tmp + 1];
    break;
  case 0x01: //LDAB
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 256 + REGISTERS[254]) * 256 + REGISTERS[255]) *256 +
          file[PC];
    REGISTERS[241] = 0;
    REGISTERS[242] = 0;
    REGISTERS[243] = 0;
    REGISTERS[244] = file[tmp];
    break;
  case 0x04: // WDAB
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 256 + REGISTERS[254]) * 256 + REGISTERS[255]) + file[PC];
    file[tmp]=REGISTERS[244];
    break;
  case 0x05: // WDAD
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 256 + REGISTERS[254]) * 256 + REGISTERS[255]) + file[PC];
    file[tmp]=REGISTERS[243];
    file[tmp+1]=REGISTERS[244];
    break;
  case 0x06: // WDAI
    PC++;
    REGISTERS[253] = file[PC];
    PC++;
    REGISTERS[254] = file[PC];
    PC++;
    REGISTERS[255] = file[PC];
    PC++;
    tmp = ((REGISTERS[253] * 256 + REGISTERS[254]) * 256 + REGISTERS[255]) + file[PC];
    file[tmp]=REGISTERS[241];
    file[tmp+1]=REGISTERS[242];
    file[tmp+2]=REGISTERS[243];
    file[tmp+3]=REGISTERS[244];
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
    tmp = ((REGISTERS[241] * 256 + REGISTERS[242]) * 256 + REGISTERS[243]) * 256 + REGISTERS[244];
    tmp+=REGISTERS[file[PC]];
    REGISTERS[244] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[243] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[242] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[241] = tmp;
    break;
  case 0x0b: // ARAD
    PC++;
    tmp = ((REGISTERS[241] * 256 + REGISTERS[242]) * 256 + REGISTERS[243]) * 256 + REGISTERS[244];
    tmp += REGISTERS[file[PC]] * 256 + REGISTERS[file[PC]+1]; 
    REGISTERS[244] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[243] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[242] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[241] = tmp;
    break;
  case 0x0c: // ARAI
    PC++;
    tmp = ((REGISTERS[241] * 256 + REGISTERS[242]) * 256 + REGISTERS[243]) * 256 + REGISTERS[244];
    tmp += ((REGISTERS[file[PC]] * 256 + REGISTERS[file[PC]+1]) * 256 + REGISTERS[file[PC]+2]) * 256 + REGISTERS[file[PC]+3];
    REGISTERS[244] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[243] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[242] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[241] = tmp;
    break;
  case 0x0d: // SRAB
    PC++;
    tmp = ((REGISTERS[241] * 256 + REGISTERS[242]) * 256 + REGISTERS[243]) * 256 + REGISTERS[244];
    tmp -= REGISTERS[file[PC]];
    REGISTERS[244] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[243] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[242] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[241] = tmp;
    break;
  case 0x0e: // SRAD
    PC++;
    tmp = ((REGISTERS[241] * 256 + REGISTERS[242]) * 256 + REGISTERS[243]) * 256 + REGISTERS[244];
    tmp -= REGISTERS[file[PC]] * 256 + REGISTERS[file[PC] + 1]; 
    REGISTERS[244] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[243] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[242] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[241] = tmp;
    break;
  case 0x0f: // SRAI
    PC++;
    tmp = ((REGISTERS[241] * 256 + REGISTERS[242]) * 256 + REGISTERS[243]) * 256 + REGISTERS[244];
    tmp -= ((REGISTERS[file[PC]] * 256 + REGISTERS[file[PC] + 1]) * 256 + REGISTERS[file[PC] + 2]) * 256 + REGISTERS[file[PC] + 3];
    REGISTERS[244] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[243] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[242] = tmp % 256;
    tmp -= tmp % 256;
    tmp = tmp / 256;
    REGISTERS[241] = tmp;
    break;
  case 0x10: //CLA
    REGISTERS[244]=0;
    REGISTERS[243]=0;
    REGISTERS[242]=0;
    REGISTERS[241]=0;
    break;
  case 0x11: //INB
    PC++;
    indentifier = file[PC] % 16;
    read(client_socket[indentifier], &REGISTERS[244], 1);
    break;
  case 0x12: //IND
    PC++;
    indentifier = file[PC] % 16;
    read(client_socket[indentifier], &REGISTERS[243], 1);
    read(client_socket[indentifier], &REGISTERS[244], 1);
    break;
  case 0x13: //INI
    PC++;
    indentifier = file[PC] % 16;
    read(client_socket[indentifier], &REGISTERS[241], 1);
    read(client_socket[indentifier], &REGISTERS[242], 1);
    read(client_socket[indentifier], &REGISTERS[243], 1);
    read(client_socket[indentifier], &REGISTERS[244], 1);
    break;
  case 0x14: //OUTB
    PC++;
    indentifier = file[PC] % 16;
    write(client_socket[indentifier], &REGISTERS[244], 1);
    break;
  case 0x15: //OUTD
    PC++;
    indentifier = file[PC] % 16;
    write(client_socket[indentifier], &REGISTERS[243], 1);
    write(client_socket[indentifier], &REGISTERS[244], 1);
    break;
  case 0x16: //OUTI
    PC++;
    indentifier = file[PC] % 16;
    write(client_socket[indentifier], &REGISTERS[241], 1);
    write(client_socket[indentifier], &REGISTERS[242], 1);
    write(client_socket[indentifier], &REGISTERS[243], 1);
    write(client_socket[indentifier], &REGISTERS[244], 1);
    break;
  }
  PC++;
  if (file[PC] == 0xFF) { // HLT
    break;
  }
  if(INTERUPTS[0] != 0){
    if(CheckInterupt(INTERUPTS[0])>=0){
      SP=PUSHINT(file, SP, PC);
      PC=InteruptJumps[INTERUPTS[0]];
    }
    ShiftInterupts(0);
  }
  REGISTERS[252] = PC % 256;
  PC -= PC % 256;
  PC = PC / 256;
  REGISTERS[251] = PC % 256;
  PC -= PC % 256;
  PC = PC / 256;
  REGISTERS[250] = PC % 256;
  PC -= PC % 256;
  PC = PC / 256;
  REGISTERS[249] = PC;
  REGISTERS[248] = SP % 256;
  SP -= SP % 256;
  SP = SP / 256;
  REGISTERS[247] = SP % 256;
  SP -= SP % 256;
  SP = SP / 256;
  REGISTERS[246] = SP % 256;
  SP -= SP % 256;
  SP = SP / 256;
  REGISTERS[245] = SP;
}