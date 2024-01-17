#include <string>

typedef unsigned char uchar;

void SafeFree(void* p);

class Mat {
protected:
    void SetZeros();
public:
    int width;
    int height;
    int channel;

    Mat();
    Mat(int width, int height, int channel);
};

class CMat: public Mat {
public:
    uchar* data;
    uchar* chnls[3]; // BGR or YUV

    CMat();
    CMat(int width, int height, int channel);

    CMat(std::string name, int width, int height, int channel);

    ~CMat();
};
