//
// Created by Noé Bonne on 3/11/21.
//

#ifndef SOUNDHOOK_FFT_H
#define SOUNDHOOK_FFT_H


//void fft(double *reel, double *imag, int log2n, int sign);

void fftCall(UIData * uiData);
int* fft(WavData* data, double* sliderValues, int treat, int equa);

#endif //SOUNDHOOK_FFT_H
