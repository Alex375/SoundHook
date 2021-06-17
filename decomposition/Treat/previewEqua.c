//
// Created by Noé Bonne on 6/17/21.
//

#include "previewEqua.h"
#include "equalizer.h"
#include "../../GraphTools/Graph.h"


#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int previewEqua(double* sliderValues, float QVal, int mode)
{
    size_t sizeIn = PRECISIONRENDER * (SVlen - 1);
    double * coefsPrint = malloc(sizeof(double) * sizeIn);
    double * xIn = malloc(sizeof (double) * sizeIn);
    for (size_t i = 0; i < sizeIn; i++)
    {
        xIn[i] = (double)i;
    }

    for (int i = 0; i < PRECISIONRENDER*(SVlen - 1); ++i) {

        double sectionF = (double) i / (double)PRECISIONRENDER;

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


    coefsPrint[0] = 0;
    coefsPrint[1] = 200.01;

    grapher(xIn, coefsPrint, sizeIn, sizeIn, "coefs.png");

    free(coefsPrint);
    free(xIn);

    return 0;
}