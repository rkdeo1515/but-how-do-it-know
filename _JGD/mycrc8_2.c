#include <stdint.h>
#include <stdio.h>
#include <string.h>

// CRC_ATM = x^8 + x^2 + x^1 + x^0

#define LEN 6

int main()
{
  int i, j, k;
  uint8_t data[100] = "hello!";
  uint8_t poly = 0x7;
  uint8_t crc = 0;
  uint8_t tmp = 0;

  crc = *data;

  for (i = 0; i < strlen((const char *)data); i++)
  {
    tmp = data[i + 1];
    for (j = 0; j < 8; j++)
    {
      if (crc >> (7 - j) & 0x1)
      {
        uint8_t div = poly >> (j + 1) | 1 << (7 - j);
        uint8_t div2 = poly << (7 - j);
        crc = crc ^ div;
        tmp = tmp ^ div2;
      }
    }
    crc = tmp;
  }
  printf("CRC:0x%X\n", crc);

  return 0;
}
