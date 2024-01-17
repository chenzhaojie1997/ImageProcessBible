#include <cassert>
#include <iostream>
#include "Mat.h"

int main() {
    CMat* p = new CMat("people.bmp2", 1024, 1023, 3);
    std::cout << p->width << ", " ;
    std::cout << p->height << ", ";
    std::cout << p->channel << "\n";
    return 0;
}