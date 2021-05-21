//
// Created by Alexandre Josien on 01/04/2021.
//

#ifndef SOUNDHOOK_TREAT_H
#define SOUNDHOOK_TREAT_H

#define RATIO_DETECT_SPIKE 2
#define LEN_DETECT_SPIKE 30
#define NB_MAX 2
#define RANGE_DESTROY 30
#define MIN_F 700

void treatOut(double* outMagn, int n_out, double time, int* iSpikes);

#endif //SOUNDHOOK_TREAT_H
