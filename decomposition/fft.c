
//
// Created by Noé Bonne on 3/11/21.
//
// FAST FOURIER TRANSFORM
// Exemple de la FFT sur la fonction f(x) = x*(1-x)

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "fft.h"
#include "Treat/Treat.h"
#include "Treat/equalizer.h"
#include "Treat/previewEqua.h"
#include </usr/local/include/fftw3.h>
#include "../GraphTools/Graph.h"
#include "../file_decoder/wav/Recoder/headers/WavRecoder.h"
#include "../GUI/type/types.h"


void fftCall(UIData * uiData)
{


    int* res = fft(uiData->soundData->data,
                   uiData->soundData->addInfo->num_of_sample,
                   uiData->soundData->header->sample_rate,
                   uiData->equalizerValue,
                   uiData->fft_active,
                   uiData->equalizerMode,
                   uiData->qFactor);
    // ->fft_active : 0=No   1 = yes with plots   2 = yes without plot
    // ->equalizerMode : 0=No   1 = yes threshold hard     2 = yes treshold soft

    free(uiData->soundData->data);
    uiData->soundData->data = res;



    // Short time FFT

    if (uiData->fft_active)
    {
        long num_of_sample = uiData->soundData->addInfo->num_of_sample;
        long sample_rate = uiData->soundData->header->sample_rate;

        int div = fabs((double)num_of_sample / (double)(sample_rate * STFFTDuration) + 0.4);
        if (div < 1)
            div = 1;
        long partLen = num_of_sample / div;

        long i = 0;
        while (i < div)
        {
            int len = partLen;
            if (i == div - 1)
                len = num_of_sample - i * partLen;

            printf("decompose fft nb %li\n", i);

            int * data = &uiData->soundData->data[i * partLen];
            int* res = fft(data,
                           len,
                           uiData->soundData->header->sample_rate,
                           uiData->equalizerValue,
                           2,
                           0,
                           1);

            for (int j = 0; j < len; ++j)
            {
                data[j] = res[j];
            }

            i++;
        }



        uiData->fft_active = 1;
    }
}


int* fft(int* data, int sizeIn, int sample_rate, double* sliderValues, int treat, int equa, double QVal)
{
    double time = (double)sizeIn / (double)sample_rate;

    double * in  = (double*)fftw_malloc(sizeof(double) * sizeIn);
    for (int i = 0; i < sizeIn; ++i)
    {
        in[i] = ((double)data[i]) ;
        //printf("%f\n", in[i]);
    }

    double * xIn = malloc(sizeof (double) * sizeIn);
    for (size_t i = 0; i < sizeIn; i++)
    {
        xIn[i] = (double)i;
    }
    if (equa || treat < 2)
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


    for (int i = 1990*3; i < 3100*3; ++i)
    {
        //printf("Magn Out %i : %f\n", i, outMagn[i]);

    }


    double * xs = malloc(sizeof (double) * n_out);
    for (size_t i = 0; i < n_out; i++)
    {
        xs[i] = (double)i / time;
    }

    if (equa || treat < 2)
        grapher(xs, outMagn, (size_t)n_out / 2, (size_t)n_out / 2, "2.fourierGraph.png");



    ///////////////////TREAT

    if (treat)
    {
        treatOut(outMagn, n_out, time, out);
    }

    if (equa)
    {
        double * coefs = malloc(sizeof(double) * n_out);


        ///////////// temp ////////

        equalizer(coefs, (int)n_out, sliderValues, time, (double)sample_rate, QVal, equa);

        //printf("\nCoefs are : \n");
        //for (int i = 0; i < n_out / 100; ++i) {
        //    printf("%f  %d\n", coefs[i * 100], i * 100 / (int)data->addInfo->time);
        //}

        for (int i = 0; i < n_out; ++i)
        {
            out[i][0] *= coefs[i] / 100;
            out[i][1] *= coefs[i] / 100;
        }


        coefs[0] = 0;
        coefs[1] = 200.01;

        //grapher(xIn, coefs, (size_t)n_out, (size_t)n_out, "coefsReal.png");
        previewEqua(sliderValues, QVal, equa);

        free(coefs);

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


    if (equa || treat < 2)
        grapher(xIn, back, (size_t)sizeIn, (size_t)sizeIn, "3.corrected.png");

    free(xIn);

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
    if (equa || treat < 2)
        grapher(xs, outMagn, (size_t)n_out / 2, (size_t)n_out / 2, "4.2nd_fourier_verif.png");


    free(xs);



    ////////////////////FREE

    fftw_destroy_plan(plan_forward);
    fftw_free(in); fftw_free(out);
    free(outMagn);

    return recod;
}