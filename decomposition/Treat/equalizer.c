//
// Created by Noé Bonne on 5/5/21.
//

#include "equalizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int equalizer(double* coefs, int n_out, double* sliderValues, double time, int mode) // mode 2 for smooth
{
    int sectionSize = n_out / SVlen;
    double decreaseExposent = 1.17;

    printf("%f", time);

    double log2of20000 = log2(20000);
    for (int i = 0; i < n_out; ++i)
    {
        int sectionN = (int)(((log2((double)i / time  + 1)- 1) * decreaseExposent * (double)SVlen) / log2of20000 ) - 1;

        if (sectionN < 0)
            sectionN = 0;

        if (sectionN >= SVlen)
            coefs[i] = sliderValues[SVlen - 1];
        else {
            if (mode == 2)
                coefs[i] = (sliderValues[i+1] * (i - n_out * sectionN / SVlen)  + sliderValues[i] * (n_out * (sectionN + 1) / SVlen - i)) / sectionSize;
            else
                coefs[i] = sliderValues[sectionN];
        }
    }

    return 0;
}
