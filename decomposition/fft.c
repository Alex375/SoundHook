
//
// Created by Noé Bonne on 3/11/21.
//
// FAST FOURIER TRANSFORM
// Exemple de la FFT sur la fonction f(x) = x*(1-x)

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Treat/Treat.h"
#include "Treat/equalizer.h"
#include </usr/local/include/fftw3.h>
#include "../GraphTools/Graph.h"
#include "../file_decoder/wav/Recoder/headers/WavRecoder.h"

int* fft(WavData* data, double* sliderValues, int treat, int equa);

void fftCall(WavData* data)
{
    double * sliderValues = malloc(sizeof(double) * SVlen);
    for (int i = 0; i < SVlen; ++i) {
        sliderValues[i] = i;
    }
    /*
    sliderValues[0] = 10;
    sliderValues[1] = 10;
    sliderValues[2] = 1;
    sliderValues[3] = 1;
    sliderValues[4] = 1;*/

    int* res = fft(data, sliderValues, 0, 1);
    free(data->data);
    data->data = res;
}


int* fft(WavData* data, double* sliderValues, int treat, int equa)
{
    int sizeIn = data->addInfo->num_of_sample;
    double time = data->addInfo->time;

    double * in  = (double*)fftw_malloc(sizeof(double) * sizeIn);
    for (int i = 0; i < sizeIn; ++i)
    {
        in[i] = ((double)data->data[i]) ;
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


    fftw_plan plan_forward;

    // real in and complex out
    plan_forward = fftw_plan_dft_r2c_1d ( sizeIn, in, out, FFTW_ESTIMATE );

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

    if (treat)
    {
        int* iSpikes = malloc(sizeof(int) * NB_MAX);
        treatOut(outMagn, n_out, time, iSpikes);

        {
            int i = 0;
            while (i < NB_MAX && iSpikes[i] != -1)
            {
                for (int j = iSpikes[i] - (RANGE_DESTROY * (int)time); j <= iSpikes[i] + (RANGE_DESTROY * (int)time); ++j)
                {
                    out[j][0] = 0;//out[(int)(maxF - (RANGE_DESTROY * time) - 1)][0];
                    out[j][1] = 0;//out[(int)(maxF - (RANGE_DESTROY * time) - 1)][1];
                }
                i++;
            }
        }

        free(iSpikes);
    }

    if (equa)
    {
        double * coefs = malloc(sizeof(double) * n_out);
        int min = n_out;

        equalizer(coefs, min, sliderValues, data->addInfo->time, equa);

        printf("\nCoefs are : \n");
        for (int i = 0; i < n_out / 100; ++i) {
            printf("%f  %d\n", coefs[i * 100], i * 100 / (int)data->addInfo->time);
        }

        for (int i = 0; i < n_out; ++i)
        {
            out[i][0] *= coefs[i];
            out[i][1] *= coefs[i];
        }
    }


    ///////////////////// invert FFT


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

    return recod;
}