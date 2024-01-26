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

    // split data into channels
    void SplitChannels();

    // read bmp in data and channels
    CMat(std::string name, int width, int height, int channel);

    // write data as bmp
    void WriteData(std::string name);

    // merge channel into data
    void MergeChannelsIntoData();

    // write channels as bmp
    void WriteChannels(std::string name);

    ~CMat();

};
