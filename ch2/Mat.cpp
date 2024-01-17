#include <iostream>
#include "Mat.h"
#include "bmp.h"

void SafeFree(void* p) {
    if (NULL != p) {
        free(p);
    }
}

void Mat::SetZeros() {
    this->width = 0;
    this->height = 0;
    this->channel = 0;
}

Mat::Mat() {
    SetZeros();
}

Mat::Mat(int width, int height, int channel) {
    this->width = width;
    this->height = height;
    this->channel = channel;
}

CMat::CMat():Mat() {
    this->data = NULL;
    for (int i = 0; i < 3; ++i) {
        this->chnls[i] = NULL;
    }
}

CMat::CMat(int width, int height, int channel):Mat(width, height, channel) {
    this->data = NULL;
    for (int i = 0; i < 3; ++i) {
        this->chnls[i] = NULL;
    }
}

CMat::CMat(std::string name, int width, int height, int channel):Mat(width, height, channel) {
    if (".bmp" != name.substr(name.length() - 4)) {
        std::cout << "CMat creating: support bmp only !" << std::endl;
        SetZeros();
        return;
    }
}

CMat::~CMat() {
    SafeFree(this->data);
    for (int i = 0; i < 3; ++i) {
        SafeFree(this->chnls[i]);
    }
}