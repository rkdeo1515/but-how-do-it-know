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

int main(int argc, char *argv[]) {
  size_t num = 0;
  uint8_t str[100] = {
      0,
  };

  // Unsigned integer -> ASCII HEX string (Static length)
  UINT8ToASCIIHex(0xf, str);
  printf("UINT8  to ASCII Hex: 0x%s\n", str);

  UINT16ToASCIIHex(0xf, str);
  printf("UINT16 to ASCII Hex: 0x%s\n", str);

  UINT32ToASCIIHex(0xf, str);
  printf("UINT32 to ASCII Hex: 0x%s\n", str);

  UINT64ToASCIIHex(0xf, str);
  printf("UINT64 to ASCII Hex: 0x%s\n", str);
  putchar('\n');

  // Unsigned integer -> ASCII HEX string (Dynamic length)
  UINTxToASCIIHex(0x0, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x01, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x012, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x01234, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x012345, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x01234567, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x012345678, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456789, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456789a, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456789ab, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456789abc, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456789abcd, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456789abcde, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);

  UINTxToASCIIHex(0x0123456789abcdef, str);
  printf("UINTx to ASCII Hex: 0x%s\n", str);
  putchar('\n');

  // ASCII HEX string -> Unsigned integer
  num = ASCIIHexToUINTx("0x0" + 2, strlen("0x0") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x01" + 2, strlen("0x01") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x012" + 2, strlen("0x012") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123" + 2, strlen("0x0123") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x01234" + 2, strlen("0x01234") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x012345" + 2, strlen("0x012345") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123456" + 2, strlen("0x0123456") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x01234567" + 2, strlen("0x01234567") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x012345678" + 2, strlen("0x012345678") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123456789" + 2, strlen("0x0123456789") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123456789a" + 2, strlen("0x0123456789a") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123456789ab" + 2, strlen("0x0123456789ab") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123456789abc" + 2, strlen("0x0123456789abc") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123456789abcd" + 2, strlen("0x0123456789abcd") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);
  num =
      ASCIIHexToUINTx("0x0123456789abcde" + 2, strlen("0x0123456789abcde") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

  num = ASCIIHexToUINTx("0x0123456789abcdef" + 2,
                        strlen("0x0123456789abcdef") - 2);
  printf("ASCII Hex to UINTx: 0x%zx\n", num);

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
