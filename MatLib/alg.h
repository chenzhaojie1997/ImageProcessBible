#ifndef ALG_H
#define ALG_H
#include "Mat.h"

template<typename T> T CLIP(T x, T a, T b);

// biliner interpolate a single-channel image
void BilinerInterpolate(uchar* outData, const int outWidth, const int outHeight, 
                        uchar* inData,  const int inWidth,  const int inHeight);

// // Interpolate by given kernel; (ox, oy) postion in old map; l/r: left/right; u/d: up/down;
// void InterpolateByKernel(uchar* outData, const int outWidth, const int outHeight, 
//                          uchar* inData,  const int inWidth,  const int inHeight, 
//                          uchar(*kernel)(int ox, int oy, uchar lu, uchar ru, uchar ld, uchar rd)); 

#endif