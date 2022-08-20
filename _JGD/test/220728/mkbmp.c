#include <stdio.h>
#include <string.h>
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
    unsigned char b;
    unsigned char g;
    unsigned char r;
} RGBPIXEL;

#pragma pack(pop)

#define BYTES_PER_PIXEL 3
#define PIXEL_ALIGN 4

RGBPIXEL color_table[7] = {
    {0x24, 0x1c, 0xed}, // red
    {0x27, 0x7f, 0xff}, // orange
    {0x00, 0xf2, 0xff}, // yello
    {0x4c, 0xb1, 0x22}, // green
    {0xe8, 0xa2, 0x00}, // blue
    {0xcc, 0x48, 0x3f}, // navy
    {0xa4, 0x49, 0xa3}  // purlple
};

int main(int argc, char *argv[])
{
    if (argc < 2 && argc > 0)
    {
        printf("Filename is missing..\n");
        return 0;
    }

    int i, j;
    int image_height = 7;
    int image_width = 7;

    // One pixel row of a bitmap image is a multiple of 4 bytes. -> Padding bytes are required
    int image_width_padding = (PIXEL_ALIGN - ((image_width * BYTES_PER_PIXEL) % PIXEL_ALIGN)) % PIXEL_ALIGN;
    int pixel_row_len = (image_width * BYTES_PER_PIXEL) + image_width_padding;

    int image_size = image_height * pixel_row_len;

    unsigned char *image_data = malloc(image_size);
    unsigned char *color_index = malloc(image_width);

    memset(image_data, 0, image_size);
    for (i = 0; i < image_width; i++)
        color_index[i] = i;

#define MODE 1

#if MODE == 0
    // This is Real Shift
    for (i = 0; i < image_height; i++)
    {
        unsigned char *ptr = &(image_data[(image_height - (i + 1)) * pixel_row_len]);

        // Write color_index as pixel row of image
        for (j = 0; j < image_width; j++)
        {
            memcpy(ptr, &color_table[color_index[j]], sizeof(*color_table));
            ptr += sizeof(*color_table);
        }
        // Shift color_index
        for (j = 0; j < image_width; j++)
            color_index[(j + i + 1) % image_width] = j;
    }
#elif MODE == 1
    // This is Fake Shift
    int shift_cnt = 0;
    for (i = 0; i < image_height; i++)
    {
        // Get pointer of next row
        unsigned char *ptr = &(image_data[(image_height - (i + 1)) * pixel_row_len]);

        // Write color_index as pixel row of image
        for (j = 0; j < image_width; j++)
        {
            memcpy(ptr, &color_table[color_index[(j + shift_cnt) % image_width]], sizeof(*color_table));
            ptr += sizeof(*color_table);
        }
        shift_cnt++;
    }
#endif

    // ----- MAKE BMP FILE -----
    FILE *fp;
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    
    fp = fopen(argv[1], "wb");

    memset(&fileHeader, 0, sizeof(fileHeader));
    memset(&infoHeader, 0, sizeof(infoHeader));

    fileHeader.bfType = *((unsigned int *)"BM");
    fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader);
    fileHeader.bfSize = fileHeader.bfOffBits + image_size;

    infoHeader.biSize = sizeof(infoHeader);
    infoHeader.biWidth = image_width;
    infoHeader.biHeight = image_height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = BYTES_PER_PIXEL * 8; // rgb 8:8:8, 24bit
    infoHeader.biSizeImage = image_size;

    fwrite(&fileHeader, sizeof(fileHeader), 1, fp);
    fwrite(&infoHeader, sizeof(infoHeader), 1, fp);

    // Go to BMP image strat point
    fseek(fp, fileHeader.bfOffBits, SEEK_SET);
    fwrite(image_data, image_size, 1, fp);

    fclose(fp);
    free(image_data);
    free(color_index);

    return 0;
}
