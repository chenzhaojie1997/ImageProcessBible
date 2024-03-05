#include <cstring>
#include <cassert>
#include <iostream>
#include "Mat.h"
#include "alg.h"

int main() {
    CMat* p = new CMat("people.bmp", 1024, 1023, 3);

    CMat* np = new CMat(4096, 4096, 3);
    for (int c = 0; c < 3; ++c) {
        MyInterpolate(np->chnls[c], np->width, np->height, 
                            p->chnls[c],  p->width,  p->height);
    }
    np->MergeChannelsIntoData();

    np->WriteData("p1.bmp");

    return 0;
}