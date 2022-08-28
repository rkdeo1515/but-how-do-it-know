#include <stdio.h>
int main(int argc, char *argv[])
{
  /*COMMAND PARSING */
  if (argc > 1 && argv[1][0] == '-')
  {
    switch (argv[1][1])
    {
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

  if (argc != 2)
  {
    printf("NO_INPUT\n");
    return -1;
  }

  static unsigned char buffer[256];

  FILE *fp = fopen(argv[1], "rb");
  if (fp == NULL)
    printf("FILE_OPEN_FAIL\n");

  fseek(fp, 0L, SEEK_END);
  int size = ftell(fp);
  rewind(fp); // fseek(fp, 0L, SEEK_SET);

  size_t cnt = fread(buffer, size, 1, fp);

  fclose(fp);

  printf("buffer(%d): %s", cnt, buffer);

  return 0;
}
