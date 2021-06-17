//
// Created by Noé Bonne on 5/5/21.
//

#ifndef SOUNDHOOK_EQUALIZER_H
#define SOUNDHOOK_EQUALIZER_H

#define SVlen 5


int equalizer(double* coefs, double* coefsPrint, int n_out, double* sliderValues, double time, double sampleRate, float QVal, int mode);

#endif //SOUNDHOOK_EQUALIZER_H
