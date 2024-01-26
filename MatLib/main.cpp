#include <cstring>
#include <cassert>
#include <iostream>
#include "Mat.h"

int main() {
    CMat* p = new CMat("people.bmp", 1024, 1023, 3);
    memset(p->data, 0, p->width * p->height * p->channel);
    p->MergeChannelsIntoData();
    p->WriteData("p0.bmp");
    return 0;
}