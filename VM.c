#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "Interrupt.c"
int server_socket[16];
int client_socket[16];
int memsize = 65536;
struct sockaddr_un server_addr[16];
struct sockaddr_un client_addr[16];
int stoh(char arg[2]) {
  int x = 0;
  switch (arg[0]) {
  case '0':
    break;
  case '1':
    x = 0x10;
    break;
  case '2':
    x = 0x20;
    break;
  case '3':
    x = 0x30;
    break;
  case '4':
    x = 0x40;
    break;
  case '5':
    x = 0x50;
    break;
  case '6':
    x = 0x60;
    break;
  case '7':
    x = 0x70;
    break;
  case '8':
    x = 0x80;
    break;
  case '9':
    x = 0x90;
    break;
  case 'a':
  case 'A':
    x = 0xA0;
    break;
  case 'b':
  case 'B':
    x = 0xB0;
    break;
  case 'c':
  case 'C':
    x = 0xC0;
    break;
  case 'd':
  case 'D':
    x = 0xD0;
    break;
  case 'e':
  case 'E':
    x = 0xE0;
    break;
  case 'f':
  case 'F':
    x = 0xF0;
    break;
  default:
    return -1;
  }
  switch (arg[1]) {
  case '0':
    break;
  case '1':
    x += 0x1;
    break;
  case '2':
    x += 0x2;
    break;
  case '3':
    x += 0x3;
    break;
  case '4':
    x += 0x4;
    break;
  case '5':
    x += 0x5;
    break;
  case '6':
    x += 0x6;
    break;
  case '7':
    x += 0x7;
    break;
  case '8':
    x += 0x8;
    break;
  case '9':
    x += 0x9;
    break;
  case 'a':
  case 'A':
    x += 0xA;
    break;
  case 'b':
  case 'B':
    x += 0xB;
    break;
  case 'c':
  case 'C':
    x += 0xC;
    break;
  case 'd':
  case 'D':
    x += 0xD;
    break;
  case 'e':
  case 'E':
    x += 0xE;
    break;
  case 'f':
  case 'F':
    x += 0xF;
    break;
  default:
    return -1;
  }
  return x;
}
void htos(char *y, int x) {
  y[1] = "0123456789abcdef"[x % 16];
  x = x - (x % 16);
  x = x / 16;
  y[0] = "0123456789abcdef"[x];
}
int options(int argc, char **argv, char *target) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], target) == 0)
      return i;
  }
  return -1;
}
int PUSHB(char *mem, int address, char value) {
  mem[address] = value;
  return address + 1;
}
int PUSHD(char *mem, int address, char value[2]) {
  mem[address] = value[0];
  mem[address+1] = value[1];
  return address + 2;
}
int PUSHI(char *mem, int address, char value[4]) {
  mem[address] = value[0];
  mem[address+1] = value[1];
  mem[address+2] = value[2];
  mem[address+3] = value[3];
  return address + 4;
}
int POPB(char *mem, int address, char *ret) {
  ret[0]=mem[address];
  return address-1;
}
int POPD(char *mem, int address, char *ret) {
  ret[0]=mem[address-1];
  ret[1]=mem[address];
  return address-2;
}
int POPI(char *mem, int address, char *ret) {
  ret[0]=mem[address-3];
  ret[1]=mem[address-2];
  ret[2]=mem[address-1];
  ret[3]=mem[address];
  return address-4;
}
int PUSHINT(char *mem, int address, int value){
  mem[address+3] = value % 256;
  value -= value % 256;
  value = value / 256;
  mem[address+2] = value % 256;
  value -= value % 256;
  value = value / 256;
  mem[address+1] = value % 256;
  value -= value % 256;
  value = value / 256;
  mem[address] = value;
  return address+4;
}
int VM(char *name) {
  FILE *f = fopen(name, "r+");
  if (f == NULL) {
    printf("ERROR: COULD NOT OPEN FILE");
    return 1;
  }
  char *file =  calloc(memsize,1);
  char header[512]="";
  bool header_done = false;
  char c;
  char tmp2[2] = "";
  bool tmp1 = false;
  while ((c = fgetc(f)) != -1) {
    if(header_done){
    if (tmp1) {
      tmp2[1] = c;
      asprintf(&file, "%s%c", file, stoh(tmp2));
      tmp1 = false;
    } else {
      tmp2[0] = c;
      tmp1 = true;
    }
    } else {
      if(c == '\n') header_done = true;
      else asprintf(&header, "%s%c", header, c);
    }
  }
  char REGISTERS[256];
  #include "PRG.c"
  return 0;
}
int as(char *name) {
  FILE *f = fopen(name, "r+");
  if (f == NULL) {
    printf("ERROR: COULD NOT OPEN FILE");
    return 1;
  }
  char *file = "";
  char c;
  while ((c = fgetc(f)) != -1) {
    asprintf(&file, "%s%c", file, c);
  }
#include "ASM.c"
  
  return 0;
}
int main(int argc, char **argv) {
  if (argc > 1) {
    int item=0;
    if ((item = options(argc, argv, "-m")) != -1){
      item++;
      memsize= atoi(argv[item]);
    }
    if ((argv[argc - 1])[0] != '-') {
      if (options(argc, argv, "-a") != -1) {
        return as(argv[argc - 1]);
      } else if (options(argc, argv, "-e") != -1) {
        return VM(argv[argc - 1]);
      } else if (options(argc, argv, "-v") != -1) {
        printf("Asembler Version:0.3.0\n");
        printf("Virtual Machine Version:0.4.0\n");
        char *date;
        struct stat attr;
        stat(argv[argc - 1], &attr);
        strftime(date, 20, "%d-%m-%y", localtime(&(attr.st_mtime)));
        if (date != 0) {
          printf("%s created on %s\n", argv[argc - 1], date);
        } else {
          printf("Cannot detrmine creation date of %s\n", argv[argc - 1]);
        }
        return 0;
      } else if (options(argc, argv, "-t") != -1) {
        int tmp = as(argv[argc - 1]);
        if (tmp == 0) {
          return VM(argv[argc - 1]);
        }
        return tmp;
      } else if (options(argc, argv, "-h")) {
        printf("-h  print this help message\n");
        printf("-a  assemble a program\n");
        printf("-e  execute a program\n");
        printf("-m  set memory size\n");
        printf("-v  print version information\n");
        printf("-t  assemble and execute a program\n");
      }
    } else {
      printf("ERROR: NO FILE PROVIDED\n");
      return 1;
    }
  } else {
    printf("ERROR: NO FILE PROVIDED\n");
    return 1;
  }
  return 0;
}
