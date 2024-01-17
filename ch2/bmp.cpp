#include <cassert>
#include <string>
#include "bmp.h"

// convert bmp Order to normal order
void BmpOrderToNormal(uchar* nrmOrder, uchar* bmpOrder, int width, int height) {
    assert(nrmOrder);
    assert(bmpOrder);

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            for (int c = 0; c < 3; ++c) {
                nrmOrder[(x * width + y) * 3 + c] = bmpOrder[((height - 1 - x) * width + y) * 3 + c];
            }
        }
    }
}

// convert normal order to BMP order
void NormalOrderToBmp(uchar* bmpOrder, uchar* nrmOrder, const int width, const int height) {
    assert(bmpOrder);
    assert(nrmOrder);

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            for (int c = 0; c < 3; ++c) {
                bmpOrder[((height - x - 1) * width + y) * 3 + c] = nrmOrder[(x * width + y) * 3 + c];
            }
        }
    }
}

void InitBmpHead(BmpHeadType* type, BmpHeadSize* size, BmpHeadFix* fix, BmpHeadColor* color, const int width, const int height) {
    assert(type);
    assert(size);
    assert(fix);
    assert(color);

    type->bmpType[0] = 'B';
    type->bmpType[1] = 'M';

    size->sizeOfFile = height * width * 3 + 54; // the whole size = size of the head + size of data
    size->reserved = 0;
    size->sizeOfBmpHead = 54; // the size of the whole head === 54
    size->sizeOfBmpInfo = 40;
    size->imgWidth = width;
    size->imgHeight = height;

    fix->fix[0] = 1;
    fix->fix[1] = 0;
    fix->bits[0] = 24; // process 24 bits defaultly
    fix->bits[1] = 0;

    color->compressedWay = 0;
    color->sizeOfBmpData = height * width * 3;
    color->horizontalResolution = 0;
    color->verticalResolution = 0;
    color->color[0] = 0;
    color->color[1] = 0;
}

bool WriteBmp(std::string name, uchar* data, const int width, const int height) {
    assert(data);

    FILE* p = fopen(name.c_str(), "wb"); // wrtie as binary file
    assert(p);

    BmpHeadType* type = (BmpHeadType*)malloc(sizeof(BmpHeadType));
    BmpHeadSize* size = (BmpHeadSize*)malloc(sizeof(BmpHeadSize));
    BmpHeadFix* fix = (BmpHeadFix*)malloc(sizeof(BmpHeadFix));
    BmpHeadColor* color = (BmpHeadColor*)malloc(sizeof(BmpHeadColor));

    assert(type);
    assert(size);
    assert(fix);
    assert(color);

    InitBmpHead(type, size, fix, color, width, height);
    
    uchar* bmpOrder = new uchar[width * height * 3];
    assert(bmpOrder);
    NormalOrderToBmp(bmpOrder, data, width, height);

    fwrite(type, 1, sizeof(BmpHeadType), p);
    fwrite(size, 4, sizeof(BmpHeadSize) / 4, p);
    fwrite(fix, 1, sizeof(BmpHeadFix), p);
    fwrite(color, 4, sizeof(BmpHeadColor) / 4, p);
    fwrite(bmpOrder, 1, height * width * 3, p);
    fclose(p);

    free(type);
    free(size);
    free(fix);
    free(color);
    delete[] bmpOrder;

    return true;
}

bool ReadBmp(std::string name, uchar* data, const int width, const int height) {
    assert(data);
    assert(width % 4 == 0);

    FILE* p = fopen(name.c_str(), "rb"); // read as binary file
    assert(p);

    fseek(p, 18, SEEK_SET); // ignore useless information

    // check input read and height
    int read_width, read_height;
    fread(&read_width, 4, 1, p);
    fread(&read_height, 4, 1, p);
    assert(read_width == width);
    assert(read_height == height);

    // read bmp
    fseek(p, 54, SEEK_SET);
    uchar* bmpOrder = (uchar*)malloc(width * height * 3);
    assert(bmpOrder);
    for (int i = 0; i < width * height * 3; ++i) {
        fread(bmpOrder + i, 1, 1, p);
    }

    // convert bmp order to normal order
    BmpOrderToNormal(data, bmpOrder, width, height);

    free(bmpOrder);

    return true;
}