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
    /*int inc = 1;
    for (int i = 1; i < n_out; ++i)
    {
        if((outMagn[i] >= outMagn[i - 1]) != inc)
            if (inc == 1)
            {
                double low = outMagn[i]+1;
                if (i-LEN_DETECT_SPIKE >= 0)
                    low = outMagn[i-LEN_DETECT_SPIKE];

                double high = outMagn[i]+1;
                if (i+LEN_DETECT_SPIKE < n_out)
                    high = outMagn[i+LEN_DETECT_SPIKE];
                if(low * RATIO_DETECT_SPIKE < outMagn[i] && high * RATIO_DETECT_SPIKE < outMagn[i])
                {

                    printf("We found a new dominating frequence : %f hertz", i / time);

                    if(i / time < 100 || i / time > 10000)
                        printf("   (sus) ");
                    printf("\n");

                }
            }
            inc = !inc;
    }*/

    //////////////

    /*
    int fullMaxI = 0;
    double fullMax = 0;
    int maxI = 0;
    for (int i = 0; i < NB_MAX; ++i) {
        for (int j = 0; j < n_out; ++j)
        {
            if (outMagn[j] > outMagn[maxI])
                maxI = j;
        }
        if (i == 0)
            fullMax = outMagn[maxI];


        int f = floor(maxI / time + 0.5);
        if(f < MIN_F || outMagn[maxI] * RATIO_DETECT_SPIKE < fullMax)
        {
            iSpikes[i] = -1;
            break;
        }


        iSpikes[i] = maxI;


        printf("The dominating frequence is : %i hertz (%i in tab) = %f", f, maxI, outMagn[maxI]);

        if(f < 70 || f > 4000)
            printf("   (sus) ");
        printf("\n");

        for (int j = -LEN_DETECT_SPIKE; j <= LEN_DETECT_SPIKE; ++j) {
            outMagn[maxI + j] = 0;
        }


    }*/



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
        v = outMagn[i];
        //printf("Inserting %f as %f in %d \n",v, outMagn[i], i);
        MediatorInsert(m,outMagn[i]);
        int newI = i - MOVING_MEDIAN_WIDTH / 2;
        movingMedian[newI] = MediatorMedian(m);
        remainder[newI] = (outMagn[newI] - movingMedian[newI]) / movingMedian[newI];
        printf("Median = %f.\n",v);
        //ShowTree(m);
    }

    double standardDeviation = 0;
    for (int i = MOVING_MEDIAN_WIDTH/2; i < n_out - MOVING_MEDIAN_WIDTH/2; ++i) {
        standardDeviation += fabs(remainder[i]);
    }
    standardDeviation /= n_out - MOVING_MEDIAN_WIDTH;
    printf("\n\nstandard deviation : %f\n", standardDeviation);


    for (int i = MOVING_MEDIAN_WIDTH/2; i < n_out - MOVING_MEDIAN_WIDTH/2; ++i) {
        if (remainder[i] > standardDeviation * 10)
            printf("%i is an annomaly ( remainder = %f)\n", (int)(i / time), remainder[i]);
    }

    int* iSpikes = malloc(sizeof(int) * NB_MAX);



    int maxI = 0;

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
        printf("\nAn anormal frequence is : %i hertz (%i in tab) = %f percent away from moving median\n", f, maxI, remainder[maxI]);

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
