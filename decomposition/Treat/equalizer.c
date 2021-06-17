//
// Created by Noé Bonne on 5/5/21.
//

#include "equalizer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int equalizer(double* coefs, double* coefsPrint, int n_out, double* sliderValues, double time, double sampleRate, float QVal, int mode) // mode 2 for smooth
{
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
        int sectionNAverage = (int)(sectionF + 0.65);


        if (sectionN >= SVlen - 1 || sectionNAverage >= SVlen - 1)
            coefs[i] = sliderValues[SVlen - 1];
        else {
            if (mode == 2)
            {
                double posInSect = sectionF - sectionN;
                double powf1 = powf(1 - posInSect, QVal);
                double powf2 = powf(posInSect, QVal);

                coefs[i] = (sliderValues[sectionN] * powf1 + sliderValues[sectionN + 1] * powf2) / (powf1 + powf2);
            }
            else
                coefs[i] = sliderValues[sectionNAverage];
        }
    }

    for (int i = 0; i < 500*(SVlen - 1); ++i) {

        double sectionF = (double) i / 500.0;

        int sectionN = (int) sectionF;
        int sectionNAverage = (int)(sectionF + 0.5);

        if (mode == 2) {
            double posInSect = sectionF - sectionN;
            double powf1 = powf(1 - posInSect, QVal);
            double powf2 = powf(posInSect, QVal);

            coefsPrint[i] = (sliderValues[sectionN] * powf1 + sliderValues[sectionN + 1] * powf2) / (powf1 + powf2);
        } else
        {
            coefsPrint[i] = sliderValues[sectionNAverage];
        }
    }





    return 0;
}
