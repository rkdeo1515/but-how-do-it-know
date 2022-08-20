/*
CRC = x^8 + x^2 + x^1 + x^0

def compute_crc8_atm(datagram, initial_value=0):
    crc = initial_value
    # Iterate bytes in data
    for byte in datagram:
        # Iterate bits in byte
        for _ in range(0, 8):
            if (crc >> 7) ^ (byte & 0x01):
                crc = ((crc << 1) ^ 0x07) & 0xFF
            else:
                crc = (crc << 1) & 0xFF
            # Shift to next bit
            byte = byte >> 1
    return crc
      unsigned char crc = 0;
  unsigned char data[LEN] = "ABC";
  int i, j;
  for (i = 0; i < LEN; i++) {
    for (j = 0; j < 8; j++) {
      if ((crc >> 7) ^ (data[i] & 0x1))
        crc = ((crc << 1) ^ 0x07) & 0xFF;
      else
        crc = (crc << 1) & 0xFF;
      data[i] = data[i] >> 1;
    }
  }

 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

// CRC_ATM = x^8 + x^2 + x^1 + x^0

#define LEN 6

void print_bin(unsigned char *b, int len);
void print_hex(unsigned char *b, int len);

int main() {
  int i, j, k;
  uint8_t data[4] = "abc";
  uint8_t enc[4 * 8] = {
      0,
  };

  printf("data: %s(len=%d)\n", data, strlen(data));

  for (i = 0; i < strlen(data); i++) {
    printf("i=%d/%d ", i, strlen(data));
    print_bin(&data[i], 1);
  }
  putchar('\n');

  for (i = 0; i < strlen(data); i++) {
    printf("i=%d/%d ", i, strlen(data));

    int tmp = data[i];
    // // print_bin((unsigned char *)&tmp, 1);
    // // putchar('\n');
    for (j = 0; j < 8; j++) {
      int k = (i + 1) * 8;
      // printf("%d ", k - j - 1);
      enc[k - j - 1] = tmp % 2;
      printf("%d", tmp % 2);
      tmp /= 2;
    }
    putchar(' ');
  }

  for (i = 0; i < strlen(data); i++)
    ;
  printf("END\n");

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