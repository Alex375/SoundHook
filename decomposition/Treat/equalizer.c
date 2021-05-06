//
// Created by Noé Bonne on 5/5/21.
//

#include "equalizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int equalizer(double* coefs, int n_out, double* sliderValues, double time, double sampleRate, int mode) // mode 2 for smooth
{
    int sectionSize = n_out / SVlen;
    double decreaseExposent = 1.17;

    double delta = 105* sampleRate / 44000;

    double log2ofMax = log2(sampleRate / 2);
    for (int i = 0; i < n_out; ++i)
    {
        double sectionF = 0;
        if ((double)i / time - delta > 0)
            sectionF = (((log2((double)i / time - delta)- 1) * decreaseExposent * (double)SVlen) / log2ofMax ) - 1;

        if (sectionF < 0)
            sectionF = 0;
        int sectionN = (int)sectionF;

        if (sectionN >= SVlen - 1)
            coefs[i] = sliderValues[SVlen - 1];
        else {
            if (mode == 2)
            {
                double posInSect = sectionF - sectionN;
                coefs[i] = (sliderValues[sectionN] * (1 - posInSect) * (1 - posInSect) + sliderValues[sectionN + 1] * posInSect * posInSect) / (posInSect * posInSect + (1 - posInSect) * (1 - posInSect));
            }
            else
                coefs[i] = sliderValues[sectionN];
        }
    }

    return 0;
}
