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

// CRC_ATM = x^8 + x^2 + x^1 + x^0 = 0x107 = 1 0000 0111

#define SIZE 100

int main()
{
  uint8_t data[SIZE] = "hello!";
  uint8_t len = strlen((const char *)data);
  uint8_t poly = 0x7;

  uint8_t i, j;
  uint8_t enc[(SIZE + 1) * 8] = {
      0,
  };
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
      enc[i + (7 - j)] = (data[i / 8] >> j) & 0x1;
    }
  }

  for (i = 0; i < len * 8; i++)
  {
    if (enc[i] == 1)
    {
      for (int j = 0; j < 9; j++)
      {
        enc[i + j] = enc[i + j] ^ div[j];
      }
    }
  }

  for (i = 0; i < 8; i++)
  {
    crc |= (enc[(len * 8) + (7 - i)] & 0x1) << i;
  }

  printf("CRC(HEX):0x%X\n", crc);

  return 0;
}
