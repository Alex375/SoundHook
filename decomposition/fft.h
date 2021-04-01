//
// Created by Noé Bonne on 3/11/21.
//

#ifndef SOUNDHOOK_FFT_H
#define SOUNDHOOK_FFT_H


//void fft(double *reel, double *imag, int log2n, int sign);


int fft(int const* decoded, int sizeIn, double time);


#endif //SOUNDHOOK_FFT_H
