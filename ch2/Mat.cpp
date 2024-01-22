#include <cassert>
#include <iostream>
#include "Mat.h"
#include "bmp.h"

void SafeFree(void* p) {
    if (NULL != p) {
        free(p);
    }
}

// Mat
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

// CMat
CMat::CMat():Mat() {
    this->data = NULL;
    for (int i = 0; i < 3; ++i) {
        this->chnls[i] = NULL;
    }
}

CMat::CMat(int width, int height, int channel):Mat(width, height, channel) {
    this->data = (uchar*) malloc(width * height * channel);
    assert(this->data);

    for (int i = 0; i < 3; ++i) {
        this->chnls[i] = (uchar*)malloc(width * height);
        assert(this->chnls[i]);
    }
}

void CMat::SplitChannels() {
    assert(this->data);
    assert(this->channel == 3);

    for (int i = 0, bid = 0, gid = 0, rid = 0; i < width * height * channel; i += 3) {
        this->chnls[0][bid++] = data[i + 0];
        this->chnls[1][gid++] = data[i + 1];
        this->chnls[2][rid++] = data[i + 2];
    }
}

CMat::CMat(std::string name, int width, int height, int channel):CMat(width, height, channel) {
    if (".bmp" != name.substr(name.length() - 4)) {
        std::cout << "CMat creating: support bmp only !" << std::endl;
        SetZeros();
        return;
    }

    assert(ReadBmp(name, this->data, this->width, this->height));
    SplitChannels();
}

void CMat::WriteData(std::string name) {
    assert(WriteBmp(name, this->data, this->width, this->height));
}

void CMat::MergeChannelsIntoData() {
    for (int i = 0; i < 3; ++i) assert(this->chnls[i]);

    for (int i = 0, bid = 0, gid = 0, rid = 0; i < width * height * channel;) {
        this->data[i++] = this->chnls[0][bid++];
        this->data[i++] = this->chnls[1][gid++];
        this->data[i++] = this->chnls[2][rid++];
    }
}

void CMat::WriteChannels(std::string name) {
    uchar* merge = (uchar*)malloc(this->width * this->height * this->channel);
    assert(merge);

    for (int i = 0, bid = 0, gid = 0, rid = 0; i < this->width * this->height * this->channel;) {
        merge[i++] = this->chnls[0][bid++];
        merge[i++] = this->chnls[1][gid++];
        merge[i++] = this->chnls[2][rid++];
    }
    
    WriteBmp(name, merge, this->width, this->height);

    free(merge);
}

CMat::~CMat() {
    SafeFree(this->data);
    for (int i = 0; i < 3; ++i) {
        SafeFree(this->chnls[i]);
    }
}
