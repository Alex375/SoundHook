//
// Created by Noé Bonne on 3/11/21.
//

#ifndef SOUNDHOOK_FFT_H
#define SOUNDHOOK_FFT_H

#define STFFTDuration 2
//void fft(double *reel, double *imag, int log2n, int sign);
#include "../GUI/type/types.h"

void fftCall(UIData * uiData);
int* fft(int* data, int sizeIn, int sample_rate, double* sliderValues, int treat, int equa);

#endif //SOUNDHOOK_FFT_H
