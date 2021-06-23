//
// Created by Alexandre Josien on 01/04/2021.
//

#include "Treat.h"
#include "Mediator/Mediator.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include </usr/local/include/fftw3.h>


void treatOut(double* outMagn, int n_out, double time, fftw_complex* out)
{


    double* movingMedian = calloc(sizeof(double), (size_t)n_out);
    double* remainder = calloc(sizeof(double), (size_t)n_out);

    Mediator* m = MediatorNew(MOVING_MEDIAN_WIDTH);

    double v = 0;
    for (int i = 0; i < MOVING_MEDIAN_WIDTH; ++i)
    {
        MediatorInsert(m,outMagn[i]);
    }

    for (int i = MOVING_MEDIAN_WIDTH; i < n_out; ++i)
    {
        MediatorInsert(m,outMagn[i]);
        int newI = i - MOVING_MEDIAN_WIDTH / 2;
        movingMedian[newI] = MediatorMedian(m);
        remainder[newI] = (outMagn[newI] - movingMedian[newI]) / movingMedian[newI];
    }

    double standardDeviation = 0;
    for (int i = MOVING_MEDIAN_WIDTH/2; i < n_out - MOVING_MEDIAN_WIDTH/2; ++i) {
        standardDeviation += fabs(remainder[i]);
    }
    standardDeviation /= n_out - MOVING_MEDIAN_WIDTH;
    printf("\n\nstandard deviation : %f\n\n", standardDeviation);


    int* iSpikes = malloc(sizeof(int) * NB_MAX);

    int i = 0;

    while(1) {
        int maxI = MOVING_MEDIAN_WIDTH/2;

        for (int j = MOVING_MEDIAN_WIDTH/2; j < n_out - MOVING_MEDIAN_WIDTH/2; ++j) {
            if (remainder[j] > remainder[maxI])
                maxI = j;
        }

        if(i == NB_MAX - 1 || remainder[maxI] < standardDeviation * NUMBER_OF_STAND_DEV)
        {
            iSpikes[i] = -1;
            break;
        }

        iSpikes[i] = maxI;

        int f = floor(maxI / time + 0.5);
        printf("\nAn abnormal frequency is : %i hertz (%i in tab) = %f percent away from moving median\n", f, maxI, remainder[maxI]);

        for (int j = -RANGE_DESTROY * (int)time; j <= RANGE_DESTROY * (int)time; ++j) {
            remainder[maxI + j] = 0;
        }

        i++;
    }

    i = 0;
    while (i < NB_MAX && iSpikes[i] != -1)
    {
        for (int j = iSpikes[i] - (RANGE_DESTROY * (int)time); j <= iSpikes[i] + (RANGE_DESTROY * (int)time); ++j)
        {
            out[j][0] = 0;//movingMedian[j];
            out[j][1] = 0;
        }
        i++;
    }

    free(iSpikes);

}
