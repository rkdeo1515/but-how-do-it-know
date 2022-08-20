#include <stdint.h>
#include <stdio.h>
#include <string.h>

// CRC_ATM = x^8 + x^2 + x^1 + x^0

#define LEN 6

void print_bin(unsigned char *b, int len);
void print_hex(unsigned char *b, int len);

int main() {
  int i, j, k;
  uint8_t data[4] = "ab";
  uint8_t enc[(4 + 1) * 8] = {
      0,
  };
  int div[] = {1, 0, 0, 0, 0, 0, 1, 1, 1};

  printf("data: %s (len=%d)\n", data, strlen(data));

  // for (i = 0; i < strlen(data); i++) {
  //   // printf("i=%d/%d ", i, strlen(data));
  //   print_bin(&data[i], 1);
  // }
  // putchar('\n');

  for (i = 0; i < strlen(data) * 8; i += 8) {
    enc[i + 7] = (data[i / 8] >> 0) & 0x1;
    enc[i + 6] = (data[i / 8] >> 1) & 0x1;
    enc[i + 5] = (data[i / 8] >> 2) & 0x1;
    enc[i + 4] = (data[i / 8] >> 3) & 0x1;
    enc[i + 3] = (data[i / 8] >> 4) & 0x1;
    enc[i + 2] = (data[i / 8] >> 5) & 0x1;
    enc[i + 1] = (data[i / 8] >> 6) & 0x1;
    enc[i + 0] = (data[i / 8] >> 7) & 0x1;
  }

  printf("data_binary: ");
  for (int i = 0; i < strlen(data) * 8; i++) {
    if ((i % 8 + (i == 0)) == 0) printf(" ");
    printf("%d", enc[i]);
  }
  putchar('\n');

  for (int i = 0; i < strlen(data) * 8; i++) {
    if (enc[i] == 1) {
      for (int j = 0; j < 9; j++) {
        enc[i + j] = enc[i + j] ^ div[j];
      }
    }
  }
  printf("CRC8: ");
  for (int i = 0; i < 8; i++) {
    if ((i % 8 + (i == 0)) == 0) printf(" ");
    printf("%d", enc[strlen(data) * 8 + i]);
  }
  putchar('\n');

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

0100 0001 0100 0010 0100 0011 0100 0100 0000 0000
 100 0001 11
      101 1000 0001 0100 0010 0100 0011 0000 0000
      100 0001 11
        1 1001 1101 0100 0010 0100 0011 0000 0000
        1 0000 0111
          1001 1010 0100 0010 0100 0011 0000 0000
          1000 0011 1
             1 1001 1100 0010 0100 0011 0000 0000
             1 0000 0111
               1001 1011 0010 0100 0011 0000 0000
               1000 0011 1
                  1 1000 1010 0100 0011 0000 0000
                  1 0000 0111
                    1000 1101 0100 0011 0000 0000
                    1000 0011 1
                         1110 1100 0011 0000 0000
                         1000 0011 1
                          110 1111 1011 0000 0000
                          100 0001 11
                           10 1110 0111 0000 0000
                           10 0000 111
                              1110 1001 0000 0000
                              1000 0011 1
                               110 1010 1000 0000
                               100 0001 11
                                10 1011 0100 0000
                                10 0000 111
                                   1011 1010 0000
                                   1000 0011 1
                                     11 1001 1000
                                     10 0000 111
                                      1 1001 0110
                                      1 0000 0111
                                        1001 0001


 */