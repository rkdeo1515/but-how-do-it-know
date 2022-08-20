#include <stdio.h>
int main(int argc, char* argv[]) {
  /*COMMAND PARSING */
  if (argc > 1 && argv[1][0] == '-') {
    switch (argv[1][1]) {
      case 'h':
        printf("PRINT_HELP\n");
        break;
      case 'v':
        printf("PRINT_VERSION\n");
        break;
      default:
        printf("NO_OPTION\n");
        break;
    }
    return -1;
  }
  if (argc != 2) {
    printf("NO_INPUT\n");
    return -1;
  }
  FILE* fp = fopen(argv[1], "rb");
  if (fp == NULL) printf("FILE_OPEN_FAIL\n");

  fseek(fp);
  int fsize;

  size_t read_c;

  return 0;
}

/*
https://techoverflow.net/2020/02/22/computing-the-crc8-atm-crc-in-python/
 */