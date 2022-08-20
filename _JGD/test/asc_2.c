#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024
#define INCREASE 0
#define RANDOM 1

#define _LOWER(x) (x >= 'A' && x <= 'Z' ? x | 0x20 : x)
#define _UPPER(x) (x >= 'a' && x <= 'z' ? x & ~0x20 : x)

void UINT8ToASCIIHex(uint8_t hex, uint8_t *ascii);
void UINT16ToASCIIHex(uint16_t hex, uint8_t *ascii);
void UINT32ToASCIIHex(uint32_t hex, uint8_t *ascii);
void UINT64ToASCIIHex(uint64_t hex, uint8_t *ascii);
void UINTxToASCIIHex(size_t hex, uint8_t *ascii);
size_t ASCIIHexToUINTx(uint8_t *ascii, uint8_t len);
int StringToASCIIHex(uint8_t *dest, uint8_t *src, uint8_t len);

int main(int argc, char *argv[]) {
  int i = 0;
  uint8_t i_str[] = "ABCDEF";
  uint8_t o_str[256] = {
      0,
  };
  printf("1:%p\n", o_str);
  if (!StringToASCIIHex(o_str, i_str, strlen(i_str))) {
    printf("IN  : %s\n", i_str);
    printf("OUT : %s\n", o_str);
    printf("OUT2: ");
    for (i = 0; i < strlen(o_str); i += 2)
      printf("0x%c%c ", o_str[i], o_str[i + 1]);
    printf("\n");
  }

  return 0;
}

void UINT8ToASCIIHex(uint8_t hex, uint8_t *ascii) {
  int i;
  uint8_t len = sizeof(hex) * 2;
  for (i = 0; i < len; i++) {
    ascii[len - (i + 1)] = (hex >> ((i)*4)) & 0xf;
  }
  for (i = 0; i < len; i++)
    ascii[i] = (ascii[i] < 0xa) ? ascii[i] + '0' : (ascii[i] - 10) + 'A';
}

void UINT16ToASCIIHex(uint16_t hex, uint8_t *ascii) {
  int i;
  uint8_t len = sizeof(hex) * 2;
  for (i = 0; i < len; i++) {
    ascii[len - (i + 1)] = (hex >> ((i)*4)) & 0xf;
  }
  for (i = 0; i < len; i++)
    ascii[i] = (ascii[i] < 0xa) ? ascii[i] + '0' : (ascii[i] - 10) + 'A';
}

void UINT32ToASCIIHex(uint32_t hex, uint8_t *ascii) {
  int i;
  uint8_t len = sizeof(hex) * 2;
  for (i = 0; i < len; i++) {
    ascii[len - (i + 1)] = (hex >> ((i)*4)) & 0xf;
  }
  for (i = 0; i < len; i++)
    ascii[i] = (ascii[i] < 0xa) ? ascii[i] + '0' : (ascii[i] - 10) + 'A';
}

void UINT64ToASCIIHex(uint64_t hex, uint8_t *ascii) {
  int i;
  uint8_t len = sizeof(hex) * 2;
  for (i = 0; i < len; i++) {
    ascii[len - (i + 1)] = (hex >> ((i)*4)) & 0xf;
  }
  for (i = 0; i < len; i++)
    ascii[i] = (ascii[i] < 0xa) ? ascii[i] + '0' : (ascii[i] - 10) + 'A';
}

void UINTxToASCIIHex(size_t hex, uint8_t *ascii) {
  int i = 0;
  uint8_t len = 0;
  size_t tmp = 0;

  do {
    tmp += ((size_t)0xf << (i++ * 4));
    len = i;
  } while (hex > tmp);

  for (i = 0; i < len; i++) {
    ascii[len - (i + 1)] = (hex >> ((i)*4)) & 0xf;
  }
  for (i = 0; i < len; i++)
    ascii[i] = (ascii[i] < 0xa) ? ascii[i] + '0' : (ascii[i] - 10) + 'A';
  ascii[len] = 0;
}

size_t ASCIIHexToUINTx(uint8_t *ascii, uint8_t len) {
  int i = 0;
  char tmp = 0;
  size_t ret = 0;

  for (i = 0; i < len; i++) {
    if (!(ascii[i] >= '0' && ascii[i] <= '9') &&
        !(ascii[i] >= 'a' && ascii[i] <= 'f') &&
        !(ascii[i] >= 'A' && ascii[i] <= 'F')) {
      puts("ERR: Invaild HEX string..");
      exit(-1);
    }
  }

  for (i = 0; i < len; i++) {
    ret = ret << 4;
    tmp = ascii[i];
    ret += (tmp >= '0' && tmp <= '9') ? tmp - '0' : _UPPER(tmp) - 'A' + 10;
    // ret += !(tmp & 0x40) ? tmp - '0' : (tmp | 0x20) - 'a' + 10;
  }
  return ret;
}

int StringToASCIIHex(uint8_t *dest, uint8_t *src, uint8_t len) {
  int i = 0;

  for (i = 0; i < len; i++) {
    if (!(src[i] >= '0' && src[i] <= '9') &&
        !(src[i] >= 'a' && src[i] <= 'f') &&
        !(src[i] >= 'A' && src[i] <= 'F')) {
      // puts("ERR: Invaild HEX string..");
      return -1;  // exit(-1);
    }
  }
  for (i = 0; i < len; i++) UINT8ToASCIIHex(src[i], dest + (i * 2));
  // while (len--) {
  //   UINT8ToASCIIHex(*src, dest);
  //   src += 1;
  //   dest += 2;
  // }
  return 0;
}