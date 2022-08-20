#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1) // Set struct align by 1 byte

typedef struct _BITMAPFILEHEADER // BMP File Header
{
    unsigned short bfType;      // BMP File Macic Number
    unsigned int bfSize;        // BMP file Size
    unsigned short bfReserved1; // Reserved 1, Must be zero
    unsigned short bfReserved2; // Reserved 2, Must be zero
    unsigned int bfOffBits;     // Offset, BMP data entry point
} BITMAPFILEHEADER;

typedef struct _BITMAPINFOHEADER // BMP DIB Header(BITMAPINFOHEADER)
{
    unsigned int biSize;         // size of BITMAPINFOHEADER struct
    int biWidth;                 // BMP Width(Pixel)
    int biHeight;                // BMP Height(Pixel)
    unsigned short biPlanes;     // Num of planesm, must be 1
    unsigned short biBitCount;   // Bits-Per-Pixel(Bit)
    unsigned int biCompression;  // Compression
    unsigned int biSizeImage;    // Size of BMP Image(Byte)
    int biXPelsPerMeter;         // Horizontal Resolution(Pixels-Per-Meter)
    int biYPelsPerMeter;         // vertical Resolution(Pixels-Per-Meter)
    unsigned int biClrUsed;      // Color indexes(Used by the bitmap)
    unsigned int biClrImportant; // Color indexes(Required for displaying the bitmap)
} BITMAPINFOHEADER;

typedef struct _RGBPIXEL // 24 Bit Pixel (8:8:8)
{
    unsigned char rgbtBlue;
    unsigned char rgbtGreen;
    unsigned char rgbtRed;

} RGBPIXEL;

#pragma pack(pop)

#define BYTES_PER_PIXEL 3
#define PIXEL_ALIGN 4

void printBITMAPFILEHEADER(BITMAPFILEHEADER fileHeader)
{
    int i = 0;
    printf("BITMAPFILEHEADER(size=%ld):\n", sizeof(fileHeader));
    printf(
        "bfType(%ld)     = %4x(x)\n"
        "bfSize(%ld)     = %4x(x) = %d(d)\n"
        "bfReserved1(%ld)= %4x(x)\n"
        "bfReserved2(%ld)= %4x(x)\n"
        "bfOffBits(%ld)  = %4x(x) = %d(d)\n",
        sizeof(fileHeader.bfType), fileHeader.bfType,
        sizeof(fileHeader.bfSize), fileHeader.bfSize, fileHeader.bfSize,
        sizeof(fileHeader.bfReserved1), fileHeader.bfReserved1,
        sizeof(fileHeader.bfReserved2), fileHeader.bfReserved2,
        sizeof(fileHeader.bfOffBits), fileHeader.bfOffBits, fileHeader.bfOffBits);
    printf("binary:\n");
    unsigned char *pt = (unsigned char *)&fileHeader;
    for (i = 0; i < sizeof(fileHeader); i++)
    {
        printf("%02x ", pt[i]);
    }
    printf("\n--------------------\n");
}

void printBITMAPINFOHEADER(BITMAPINFOHEADER infoHeader)
{
    int i = 0;
    printf("BITMAPINFOHEADER(size=%ld):\n", sizeof(infoHeader));
    printf("biSize(%ld)         = %4x(x) = %d(d)\n"
           "biWidth(%ld)        = %4x(x) = %d(d)\n"
           "biHeight(%ld)       = %4x(x) = %d(d)\n"
           "biPlanes(%ld)       = %4x(x)\n"
           "biBitCount(%ld)     = %4x(x) = %d(d)\n"
           "biCompression(%ld)  = %4x(x)\n"
           "biSizeImage(%ld)    = %4x(x) = %d(d)\n"
           "biXPelsPerMeter(%ld)= %4x(x)\n"
           "biYPelsPerMeter(%ld)= %4x(x)\n"
           "biClrUsed(%ld)      = %4x(x)\n"
           "biClrImportant(%ld) = %4x(x)\n",
           sizeof(infoHeader.biSize), infoHeader.biSize, infoHeader.biSize,
           sizeof(infoHeader.biWidth), infoHeader.biWidth, infoHeader.biWidth,
           sizeof(infoHeader.biHeight), infoHeader.biHeight, infoHeader.biHeight,
           sizeof(infoHeader.biPlanes), infoHeader.biPlanes,
           sizeof(infoHeader.biBitCount), infoHeader.biBitCount, infoHeader.biBitCount,
           sizeof(infoHeader.biCompression), infoHeader.biCompression,
           sizeof(infoHeader.biSizeImage), infoHeader.biSizeImage, infoHeader.biSizeImage,
           sizeof(infoHeader.biXPelsPerMeter), infoHeader.biXPelsPerMeter,
           sizeof(infoHeader.biYPelsPerMeter), infoHeader.biYPelsPerMeter,
           sizeof(infoHeader.biClrUsed), infoHeader.biClrUsed,
           sizeof(infoHeader.biClrImportant), infoHeader.biClrImportant);
    printf("binary:\n");
    unsigned char *pt = (unsigned char *)&infoHeader;
    for (i = 0; i < sizeof(infoHeader); i++)
    {
        printf("%02x ", pt[i]);
    }
    printf("\n--------------------\n");
}

void printBITMAPIMAGE(unsigned char *img, int len)
{

    printf("BITMAPIMAGE(size=%d)\n", len);
    printf("binary:\n");
    int i = 0;
    while (i < len)
    {
        printf("%02x ", img[i++]);
    }
    printf("\n--------------------\n");
}

int main(int argc, char *argv[])
{

    if (argc < 2 && argc > 0)
    {
        printf("Filename is missing..\n");
        return 0;
    }

    FILE *fp;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    int image_width;
    int image_height;
    int image_size;
    unsigned char *image_data;

    fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        printf("fopen..FAIL\n");
        return 0;
    }
    else
    {
        printf("fopen..DONE\n");
    }

    if (fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
    {
        printf("Read BITMAPFILEHEADER..FAIL\n");
        fclose(fp);
        return 0;
    }
    else
    {
        printf("Read BITMAPFILEHEADER..DONE\n");
    }

    // if (fileHeader.bfType != 'MB')
    if (fileHeader.bfType != *((unsigned short *)"BM"))
    {
        printf("Check bfType(Magic Number=BM)..FAIL\n");
        fclose(fp);
        return 0;
    }
    else
    {
        printf("Check bfType(Magic Number=BM)..DONE\n");
    }

    if (fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp) < 1)
    {
        printf("Read BITMAPINFOHEADER..FAIL\n");
        fclose(fp);
        return 0;
    }
    else
    {
        printf("Read BITMAPINFOHEADER..DONE\n");
    }

    if (infoHeader.biBitCount != 24)
    {
        printf("Check biBitCount(=24bit)..FAIL\n");

        fclose(fp);
        return 0;
    }
    else
    {
        printf("Check biBitCount(=24bit)..DONE\n");
    }

    image_size = infoHeader.biSizeImage;
    image_width = infoHeader.biWidth;
    image_height = infoHeader.biHeight;
    image_data = malloc(image_size);

    // Go to BMP image strat point
    fseek(fp, fileHeader.bfOffBits, SEEK_SET);

    if (fread(image_data, image_size, 1, fp) < 1)
    {
        printf("Read image data..FAIL\n");
        fclose(fp);
        return 0;
    }
    else
    {
        printf("Read image data..Done\n");
    }

    printf("\n--------------------\n");
    printBITMAPFILEHEADER(fileHeader);
    printBITMAPINFOHEADER(infoHeader);
    printBITMAPIMAGE(image_data, image_size);
    free(image_data);
    fclose(fp);

    return 0;
}