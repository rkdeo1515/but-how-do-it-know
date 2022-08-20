#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char data[1024] = {0};
  char encode[1024] = {0};
  int divisor[] = {1, 0, 0, 0, 0, 0, 1, 1, 1};
  printf("CRC-8 Generator\n");
  printf("8bit ASCII code\n");
  printf("Divisor : x^8+x^2+x+1 (100000111)\n\n");
  printf("  Data\t: ");

  // scanf("%s", data);
  data[0] = 'a';
  data[1] = 'b';
  data[2] = 'c';
  data[3] = '\0';
  printf("%s", data);

  // encode에 2진수를 바이트 단위로 뒤집어 집어 넣음
  for (int i = 0; i < strlen(data); i++) {
    int tmp = data[i];
    for (int j = 0; j < 8; j++) {
      int k = (i + 1) * 8;
      encode[k - j - 1] = tmp % 2;
      tmp /= 2;
    }
  }

  printf("\n  BinD\t:");
  for (int i = 0; i < strlen(data) * 8; i++) {
    if (i % 8 == 0) printf(" ");
    printf("%d", encode[i]);
  }

  for (int i = 0; i < strlen(data) * 8; i++) {
    if (encode[i] == 1) {
      for (int j = 0; j < 9; j++) {
        encode[i + j] = encode[i + j] ^ divisor[j];
      }
    }
  }

  printf("\n  CRC\t: ");
  for (int i = 0; i < 8; i++) {
    int tmp = (int)strlen(data) * 8;
    printf("%d", encode[tmp + i]);
  }
  printf("\n\n");

  return 0;
}