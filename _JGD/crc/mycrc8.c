#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CRC_ATM = x^8 + x^2 + x^1 + x^0
// https://crccalc.com/

uint8_t crc8_atm2(uint8_t *data, uint8_t poly);
uint8_t CRC8(const char *data, int length);

uint8_t crc8_arr(uint8_t *data, uint8_t len, uint8_t poly);
uint8_t crc8_byte(uint8_t *data, uint8_t len, uint8_t poly);
void print_bin(unsigned char *b, int len)
{
  int i, j;
  for (i = 0; i < len; i++)
    for (j = 0; j < 8; j++)
      printf("%d", (b[len - (i + 1)] >> 8 - (j + 1)) & 0x1);
  putchar(' ');
  // printf("%d%c", (b[len - (i + 1)] >> 8 - (j + 1)) & 0x1,
  //        ((j + 1) % 4 == 0) ? ' ' : '\0');
}
int main()
{
  uint8_t poly = 0x7;
  // poly = 0x1D;
  poly = 0x31;
  uint8_t *data = "AB";

  printf("data=%2x ", *data);
  print_bin(data, 1);
  printf("\n");

  printf("CRC_ARR:0x%X\n", crc8_byte(data, strlen(data), 0x7));
  printf("CRC_BYTE:0x%X\n", crc8_byte(data, strlen(data), 0x31));
  printf("CRC_BYT2:0x%X\n", crc8_byte(data, strlen(data), poly));

  printf("CRC8:0x%X\n", CRC8(data, strlen(data)));

  return 0;
}
uint8_t CRC8(const char *data, int length)
{
  int i, j;
  uint8_t poly = 0x8c; // 0x131 maxim
  uint8_t crc = 0x00;
  uint8_t tmp;
  uint8_t sum;

  printf("poly=%2x ", poly);
  print_bin(&poly, 1);
  printf("\n");

  for (i = 0; i < length; i++)
  {
    tmp = *data;

    for (j = 0; j < 8; j++)
    {
      sum = (crc ^ tmp) & 0x01;

      printf("[%d:%d]:\t", i, j);
      printf("tmp=\t");
      print_bin(&tmp, 1);
      printf("\n\t");
      printf("crc=\t");
      print_bin(&crc, 1);
      // printf("\n\t");
      // printf("sum=\t");
      // print_bin(&sum, 1);
      printf("\n\n");
      // printf("\n");

      crc >>= 1;
      // printf("crc>>1=\t");
      // print_bin(&crc, 1);
      // printf("\n\n");
      // printf("\n");

      if (sum)
      {
        printf("\tcrc=\t");
        print_bin(&crc, 1);
        printf("\n\t");
        printf("poly=\t");
        print_bin(&poly, 1);
        printf("\n\t");
        crc ^= poly;
        printf("xor=\t");
        print_bin(&poly, 1);
        printf("\n\t");
        printf("\n");
      }
      tmp >>= 1;
    }
    data++;
  }

  // printf("res=%2x ", crc);
  // print_bin(&crc, 1);
  // printf("\n");

  return crc;
}

/*

      printf("[%d:%d]: ", i, j);
      printf("tmp=%2x ", tmp);
      print_bin(&tmp, 1);
      printf("crc=%2x ", crc);
      print_bin(&crc, 1);
      printf("crc^poly=%2x ", sum);
      printf("%s", sum ? "*" : " ");
      printf("\n");

A -> 18 0001 1000
poly 1 0011 0001
8c 1000 1100
A 0x41 :0100 0001

MAXIM
0100 0001 0000 0000
 100 1100 01
     1101 0100 0000
        1 0011 0001
          0100 0001



0100 0001 0000 0000
 100 0110 0
      111 0000 0000
      100 0110 0
       11 0110 0000
       10 0011 00
        1 0101 0000
        1 0001 100
          0100 1000

ATM
0100 0001 0000 0000
 100 0001 11
          1100 0000


1D 0001 1101
EBU 1B
0100 0001 0000 0000
 100 0111 01
      110 0100 0000
      100 0111 01



*/
uint8_t crc8_test(uint8_t *data, uint8_t poly)
{
  int i, j;
  uint8_t crc, tmp;

  crc = *data;

  for (i = 0; i < strlen((const char *)data); i++)
  {
    tmp = data[i + 1];
    for (j = 0; j < 8; j++)
    {
      if (crc >> (7 - j) & 0x1)
      {
        uint8_t div_high = poly >> (j + 1) | 1 << (7 - j);
        uint8_t div_low = poly << (7 - j);
        crc = crc ^ div_high;
        tmp = tmp ^ div_low;
      }
    }
    crc = tmp;
  }

  return crc;
}

uint8_t crc8_byte(uint8_t *data, uint8_t len, uint8_t poly)
{
  int i, j;
  uint8_t crc, tmp;

  crc = *data;

  for (i = 0; i < len; i++)
  {
    tmp = data[i + 1];
    for (j = 0; j < 8; j++)
    {
      if (crc >> (7 - j) & 0x1)
      {
        uint8_t div_high = poly >> (j + 1) | 1 << (7 - j);
        uint8_t div_low = poly << (7 - j);
        crc = crc ^ div_high;
        tmp = tmp ^ div_low;
      }
    }
    crc = tmp;
  }

  return crc;
}
uint8_t crc8_byte2(uint8_t *data, uint8_t len, uint8_t poly)
{
  int i, j;
  uint8_t crc, tmp;

  crc = *data;
  poly = ~poly;

  for (i = 0; i < len; i++)
  {
    tmp = data[i + 1];
    for (j = 0; j < 8; j++)
    {
      if (crc >> (7 - j) & 0x1)
      {
        // uint8_t div_high = poly >> (j + 1) | 1 << (7 - j);
        uint8_t div_high = poly >> (j + 1);
        uint8_t div_low = poly << (7 - j);
        crc = crc ^ div_high;
        tmp = tmp ^ div_low;
      }
    }
    crc = tmp;
  }

  return crc;
}

uint8_t crc8_arr(uint8_t *data, uint8_t len, uint8_t poly)
{
  uint8_t i, j;
  uint8_t *tmp = malloc((len + 1) * 8);
  uint8_t div[9];
  uint8_t crc = 0;

  // 0x07 -> {1, 0, 0, 0, 0, 0, 1, 1, 1};
  div[0] = 1;
  for (i = 1; i < 9; i++)
  {
    div[9 - i] = (poly & 0x1) % 2;
    poly /= 2;
  }

  for (i = 0; i < len * 8; i += 8)
  {
    for (j = 0; j < 8; j++)
    {
      tmp[i + (7 - j)] = (data[i / 8] >> j) & 0x1;
    }
  }

  for (i = 0; i < len * 8; i++)
  {
    if (tmp[i] == 1)
    {
      for (int j = 0; j < 9; j++)
      {
        tmp[i + j] = tmp[i + j] ^ div[j];
      }
    }
  }

  for (i = 0; i < 8; i++)
  {
    crc |= (tmp[(len * 8) + (7 - i)] & 0x1) << i;
  }
  free(tmp);
  return crc;
}