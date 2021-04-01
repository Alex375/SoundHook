
//
// Created by Noé Bonne on 3/11/21.
//
// FAST FOURIER TRANSFORM
// Exemple de la FFT sur la fonction f(x) = x*(1-x)

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include </usr/local/include/fftw3.h>
#include "../GraphTools/Graph.h"
#include "../file_decoder/wav/Recoder/Recoder.h"


#define RATIO_DETECT_SPIKE 3
#define LEN_DETECT_SPIKE 30
#define NB_MAX 10

#define RANGE_DESTROY 100

int treatOut(double* outMagn, int n_out, double time)
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
            fullMaxI = maxI;
            fullMax = outMagn[maxI];
        if(outMagn[maxI] * RATIO_DETECT_SPIKE < fullMax)
            break;



        int f = floor(maxI / time + 0.5);

        printf("The dominating frequence is : %i hertz (%i in tab)", f, maxI);

        if(f < 70 || f > 4000)
            printf("   (sus) ");
        printf("\n");

        for (int j = -LEN_DETECT_SPIKE; j <= LEN_DETECT_SPIKE; ++j) {
            outMagn[maxI + j] = 0;
        }


    }

    return fullMaxI;


}



// fft init
// real numbers in
int fft(int const* decoded, int sizeIn, double time)
{
    double * in  = (double*)fftw_malloc(sizeof(double) * sizeIn);
    for (int i = 0; i < sizeIn; ++i)
    {
        in[i] = ((double)decoded[i]) ;
        //printf("%f\n", in[i]);
    }

    double * xIn = malloc(sizeof (double) * sizeIn);
    for (size_t i = 0; i < sizeIn; i++)
    {
        xIn[i] = (double)i;
    }

    grapher(xIn, in, (size_t)sizeIn, (size_t)sizeIn, "1.original.png");



    int n_out = ((sizeIn/2)+1);
// complex numbers out
    fftw_complex* out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * n_out);

    /* false in fill
    for (int i = 0; i < sizeIn; ++i)
    {
        in[i] = sin(i*2*M_PI/2.2 + M_PI/2) * 10;

    }*/



    fftw_plan plan_forward;

    // real in and complex out
    plan_forward = fftw_plan_dft_r2c_1d ( sizeIn, in, out, FFTW_ESTIMATE );

    // do it
    fftw_execute ( plan_forward );


    double * outMagn = malloc(sizeof(double) * n_out);
    for (int i = 0; i < n_out; ++i)
    {
        double mag = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        outMagn[i] = mag;
    }

    double max = 0;
    for (int j = 0; j < n_out; ++j)
    {
        if (outMagn[j] > max)
            max = outMagn[j];
    }

    for (int i = 0; i < n_out; ++i)
    {
        outMagn[i] = outMagn[i]/max*1000;
    }

    for (int i = 1990*3; i < 3100*3; ++i)
    {
        //printf("Magn Out %i : %f\n", i, outMagn[i]);

    }

    double * xs = malloc(sizeof (double) * n_out);
    for (size_t i = 0; i < n_out; i++)
    {
        xs[i] = (double)i / time;
    }

    grapher(xs, outMagn, (size_t)n_out / 2, (size_t)n_out / 2, "2.fourierGraph.png");



    ///////////////////TREAT


    int maxF = treatOut(outMagn, n_out, time);

    for (int i = maxF - (RANGE_DESTROY * time); i <= maxF + (RANGE_DESTROY * time); ++i)
    {
        out[i][0] = 0;//out[(int)(maxF - (RANGE_DESTROY * time) - 1)][0];
        out[i][1] = 0;//out[(int)(maxF - (RANGE_DESTROY * time) - 1)][1];
    }

    ///////////////////// ivert FFT


    fftw_plan ifft;
    double * back  = (double*)fftw_malloc(sizeof(double) * sizeIn);

    ifft = fftw_plan_dft_c2r_1d(sizeIn, out, back, FFTW_ESTIMATE);

    fftw_execute(ifft);
    for (size_t i = 0; i < sizeIn; i++)
    {
        back[i] /= sizeIn;
    }

    int* recod = malloc(sizeof (int) * sizeIn);
    for (size_t i = 0; i < sizeIn; i++)
    {
        recod[i] = (int)back[i];
    }
    FILE* f = fopen("/Users/alexandrejosien/Desktop/SoundHook/file_decoder/sounds/b.wav", "r");
    recodeWav(recod, f, sizeIn);


    grapher(xIn, back, (size_t)sizeIn, (size_t)sizeIn, "3.corrected.png");


    ////////////////VERIF FFT

    plan_forward = fftw_plan_dft_r2c_1d ( sizeIn, back, out, FFTW_ESTIMATE );

    // do it
    fftw_execute ( plan_forward );

    for (int i = 0; i < n_out; ++i)
    {
        double mag = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        outMagn[i] = mag;
    }

    max = 0;
    for (int j = 0; j < n_out; ++j)
    {
        if (outMagn[j] > max)
            max = outMagn[j];
    }

    for (int i = 0; i < n_out; ++i)
    {
        outMagn[i] = outMagn[i]/max*1000;
    }
    grapher(xs, outMagn, (size_t)n_out / 2, (size_t)n_out / 2, "4.2nd_fourier_verif.png");






    ////////////////////FREE

    fftw_destroy_plan(plan_forward);
    fftw_free(in); fftw_free(out);
    free(outMagn);
    return 0;
}