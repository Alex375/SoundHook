//
// Created by Alexandre Josien on 01/04/2021.
//
#include </usr/local/include/fftw3.h>


#ifndef SOUNDHOOK_TREAT_H
#define SOUNDHOOK_TREAT_H

#define NB_MAX 6
#define RANGE_DESTROY 30
#define NUMBER_OF_STAND_DEV 21

#define MOVING_MEDIAN_WIDTH 100

void treatOut(double* outMagn, int n_out, double time, fftw_complex* out);

#endif //SOUNDHOOK_TREAT_H
