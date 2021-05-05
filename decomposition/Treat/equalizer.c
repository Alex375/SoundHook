//
// Created by Noé Bonne on 5/5/21.
//

#include "equalizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int equalizer(double* coefs, int n_out, double* sliderValues, int SVlen, char* mode) // mode "S" for smooth
{
    for (int i = 0; i < n_out; ++i)
    {
        int sectionN = i * SVlen / n_out;
        int sectionSize = n_out / SVlen;

        if (strncmp(mode,  "S", 1) == 0)
            coefs[i] = (sliderValues[i+1] * (i - n_out * sectionN / SVlen)  + sliderValues[i] * (n_out * (sectionN + 1) / SVlen - i)) / sectionSize;
        else
            coefs[i] = sliderValues[(i + sectionSize/2) * SVlen / n_out];
    }

    return 0;
}
