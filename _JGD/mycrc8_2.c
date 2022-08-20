#include <stdint.h>
#include <stdio.h>
#include <string.h>

// CRC_ATM = x^8 + x^2 + x^1 + x^0

#define LEN 6

void print_bin(unsigned char *b, int len);
void print_hex(unsigned char *b, int len);

int main() {
  int i, j, k;
  uint8_t data[10] = "abcd";
  uint8_t div = 0x7;
  // int div[] = {1, 0, 0, 0, 0, 0, 1, 1, 1};

  printf("data: %s (len=%d)\n", data, strlen(data));

  printf("binary: ");
  for (i = 0; i < strlen(data); i++) {
    for (j = 0; j < 8; j++) {
      uint8_t tmp = data[i] >> (7 - j) & 0x1;
      printf("%d", tmp);
    }
    putchar(' ');
  }
  putchar('\n');
  uint8_t crc;
  for (i = 0; i < strlen(data) * 8; i++) {
    // uint8_t tmp = data[i / 8] >> (7 - i % 8) & 0x1;
    uint8_t tmp = data[i / 8];
    if (tmp >> (7 - i % 8) & 0x1) {
      for (j = 0; j < 8; j++) {
        printf("%x ", tmp);
      }
      putchar(' ');
    }
  }
  //   if (enc[i] == 1) {
  //     for (int j = 0; j < 9; j++) {
  //       enc[i + j] = enc[i + j] ^ div[j];
  //     }
  //   }
  // }
  // printf("CRC8: ");
  // for (int i = 0; i < 8; i++) {
  //   if ((i % 8 + (i == 0)) == 0) printf(" ");
  //   printf("%d", enc[strlen(data) * 8 + i]);
  // }
  // putchar('\n');

  printf("\nEND\n");
  return 0;
}

void print_bin(unsigned char *b, int len) {
  int i, j;
  for (i = 0; i < len; i++)
    for (j = 0; j < 8; j++)
      printf("%d", (b[len - (i + 1)] >> 8 - (j + 1)) & 0x1);
  putchar(' ');
  // printf("%d%c", (b[len - (i + 1)] >> 8 - (j + 1)) & 0x1,
  //        ((j + 1) % 4 == 0) ? ' ' : '\0');
}

void print_hex(unsigned char *b, int len) {
  int i, j;
  for (i = 0; i < len; i++) printf("%h ", b[len - (i + 1)]);
}

/*

crc8-CCITT = x^8 + x^2 + x^1 + x^0 = 10000 0111
---
A 0x41 :0100 0001
B 0x42 :0100 0010
C 0x43 :0100 0011
D 0x44 :0100 0100

100000111
a
01100001 00000000
 1000001 11
  100000 11000000
  100000 111
         00100000


b
01100010 00000000
 1000001 11
  100011 11000000
  100000 111
      11 00100000
      10 0000111
       1 00101110
       1 00000111
         00101001

ab
01100001 01100010 00000000
 1000001 11
  100000 10100010
  100000 111
          1000010

 */