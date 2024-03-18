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
printf("%s", file);
while (true) {
  PC = ((REGISTERS[249] * 16 + REGISTERS[250]) * 16 + REGISTERS[251]) * 16 +
       REGISTERS[252];
  printf("%d:%d\n", PC, file[PC]);
  switch (file[PC]) {
  case 0x02:
    PC++;
    // REGISTERS
    break;
  case 0x03:
  }
  PC++;
  if (file[PC] == 0x01) {
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