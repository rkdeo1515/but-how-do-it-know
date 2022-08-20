#include <stdint.h>
#include <stdio.h>
#include <string.h>

// CRC_ATM = x^8 + x^2 + x^1 + x^0

uint8_t crc8_atm(uint8_t *data);
uint8_t crc8_atm2(uint8_t *data);

int main()
{
  uint8_t data[] = "hello!";
  printf("CRC:0x%X\n", crc8_atm2(data));

  return 0;
}

uint8_t crc8_atm2(uint8_t *data)
{
  int i, j;
  uint8_t poly = 0x7;
  uint8_t crc, tmp;
  uint16_t tmp2;

  tmp2 = *(uint16_t *)data;
  // printf("%x\n", tmp2);
  // tmp2 = *(uint16_t *)(data + 1);
  // printf("%x\n", tmp2);

  for (j = 0; j < 16; j++)
  {
    if ((j % 8 + (j == 0)) == 0)
      printf(" ");

    printf("%d", tmp2 >> 16 - j & 1);
  }
  putchar('\n');

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

uint8_t crc8_atm(uint8_t *data)
{
  int i, j;
  uint8_t poly = 0x7;
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