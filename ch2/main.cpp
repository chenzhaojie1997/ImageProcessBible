#include <cassert>
#include <iostream>
#include "bmp.h"

int main() {
    int width = 1024;
    int height = 1023;
    unsigned char* data = new unsigned char[width * height * 3];    
    assert(data);

    bool ret = ReadBmp("./people.bmp", data, width, height);
    std::cout << ret << std::endl;

    ret = WriteBmp("./p.bmp", data, width, height);
    std::cout << ret << std::endl;

    delete[] data;
    return 0;
}