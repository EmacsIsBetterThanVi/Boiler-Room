#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "Interrupt.c"
int options(int argc, char **argv, char *target) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], target) == 0)
      return i;
  }
  return -1;
}
int VM(char *name) {
  FILE *f = fopen(name, "r+");
  if (f == NULL) {
    printf("ERROR: COULD NOT OPEN FILE");
    return 1;
  }
  char *file = "";
  char s[10];
  while (fgets(s, 10, f)) {
    asprintf(&file, "%s%s", file, s);
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
  char s[10];
  while (fgets(s, 10, f)) {
    asprintf(&file, "%s%s", file, s);
  }
#include "ASM.c"
  return 0;
}
int main(int argc, char **argv) {
  if (argc > 1) {
    if ((argv[argc - 1])[0] != '-') {
      if (options(argc, argv, "-a") != -1) {
        return as(argv[argc - 1]);
      } else if (options(argc, argv, "-e") != -1) {
        return VM(argv[argc - 1]);
      } else if (options(argc, argv, "-v") != -1) {
        printf("Asembler Version:0.0.0\n");
        printf("Virtual Machine Version:0.0.0\n");
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