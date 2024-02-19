#include <cassert>
#include "alg.h"

template<typename T> T CLIP(T x, T a, T b) {
    if (x <= a) return a;
    if (x >= b) return b;
    return x;
}

void BilinerInterpolate(uchar* outData, const int outWidth, const int outHeight,
                        uchar* inData,  const int inWidth,  const int inHeight) {
    assert(outData);
    assert(inData);

    float x_scale = outWidth / inWidth;
    float y_sclae = outHeight / inHeight;

    for (int ny = 0; ny < outHeight; ++ny) {
        for (int nx = 0; nx < outWidth; ++nx) {
            float oy = ny / y_sclae;
            float ox = nx / x_scale;

            int iy = int(oy);
            int ix = int(ox);

            int value = 0;
            if (iy >= 0 && iy < inHeight - 1 && ix >= 0 && ix < inWidth - 1) {
                value = (1 - oy + iy) * (1 - ox + ix) * inData[iy * inWidth +       ix]     + \
                        (1 - oy + iy) * (ox - ix)     * inData[iy * inWidth +       ix + 1] + \
                        (oy - iy)     * (1 - ox + ix) * inData[(iy + 1) * inWidth + ix]     + \
                        (oy - iy)     * (ox - ix)     * inData[(iy + 1) * inWidth + ix + 1];
                
                value = CLIP(value, 0, 255);
            }

            outData[ny * outWidth + nx] = uchar(value);

        }
    }
}