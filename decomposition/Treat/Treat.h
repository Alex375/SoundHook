//
// Created by Alexandre Josien on 01/04/2021.
//

#ifndef SOUNDHOOK_TREAT_H
#define SOUNDHOOK_TREAT_H

#define RATIO_DETECT_SPIKE 2
#define LEN_DETECT_SPIKE 30
#define NB_MAX 10

#define RANGE_DESTROY 15

void treatOut(double* outMagn, int n_out, double time, int* iSpikes);

#endif //SOUNDHOOK_TREAT_H
