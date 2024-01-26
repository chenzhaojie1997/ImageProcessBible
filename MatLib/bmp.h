#ifndef _BMP_H_
#define _BMP_H_
#include <string>

typedef unsigned char uchar;

class BmpHeadType {
public:
    char bmpType[2]; // alaways 'B' 'M'
}; 

class BmpHeadSize {
public:
    int sizeOfFile;
    int reserved;
    int sizeOfBmpHead; // size of the whole BMP head
    int sizeOfBmpInfo; // size of information part of the BMP head
    int imgWidth;
    int imgHeight;
};

class BmpHeadFix {
public:
    char fix[2];
    char bits[2]; // BMP bits
};

class BmpHeadColor {
public:
    int compressedWay;
    int sizeOfBmpData;
    int horizontalResolution;
    int verticalResolution;
    int color[2];
};

bool ReadBmp(std::string name, uchar* data, const int width, const int height);
bool WriteBmp(std::string name, uchar* data, const int width, const int height);
void InitBmpHead(BmpHeadType* type, BmpHeadSize* size, BmpHeadFix* fix, BmpHeadColor* color, const int width, const int height);

#endif
