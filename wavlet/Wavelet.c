//
// Created by Alexandre Josien on 04/05/2021.
//

#include "headers/Wavelet.h"
#include "../file_decoder/wav/types/wav.h"
#include "../file_decoder/wav/tools/headers/WavTools.h"
#include "../wavelib/header/wavelib.h"
#include "../wavelib/header/wauxlib.h"
#include <stdlib.h>
#include <math.h>
#include "../GUI/type/types.h"


void denoiseSignal(UIData* data)
{
    denoise_object denoiseObject = denoise_init((int)data->soundData->addInfo->num_of_sample, 4, "meyer");
    double* res = malloc(sizeof (double) * data->soundData->addInfo->num_of_sample);
    double* temp = malloc(sizeof (double) * data->soundData->addInfo->num_of_sample);
    for (size_t i = 0; i < data->soundData->addInfo->num_of_sample; i++)
    {
        temp[i] = (double)data->soundData->data[i];
    }
    denoise(denoiseObject, temp, res);
    free(temp);
    for (size_t i = 0; i < data->soundData->addInfo->num_of_sample; i++)
    {
        data->soundData->data[i] = (int)res[i];
    }

}



//double absmax(double *array, int N) {
//    double max;
//    int i;
//    max = 0.0;
//    for (i = 0; i < N; ++i) {
//        if (fabs(array[i]) >= max) {
//            max = fabs(array[i]);
//        }
//    }
//    return max;
//}
//
//
//int wavelet(WavData* wavData)
//{
//    wave_object obj;
//    wt_object wt;
//    double *inp, *out, *diff;
//    int N, i, J;
//    double temp[1200];
//    char *name = "db4";
//    obj = wave_init(name);// Initialize the wavelet
//
//    N = wavData->addInfo->num_of_sample;
//    inp = (double *) malloc(sizeof(double) * N);
//    out = (double *) malloc(sizeof(double) * N);
//    diff = (double *) malloc(sizeof(double) * N);
//
//
//
//
//    //wmean = mean(temp, N);
//    for (i = 0; i < N; ++i) {
//        inp[i] = wavData->data[i];
//        //printf("%g \n",inp[i]);
//    }
//    J = 3;
//    wt = wt_init(obj, "dwt", N, J);// Initialize the wavelet transform object
//    setDWTExtension(wt, "sym");// Options are "per" and "sym". Symmetric is the default option
//    setWTConv(wt, "direct");
//    dwt(wt, inp);// Perform DWT
//    //DWT output can be accessed using wt->output vector. Use wt_summary to find out how to extract appx and detail coefficients
//    /*for (i = 0; i < wt->outlength; ++i) {
//        printf("%g ", wt->output[i]);
//    }*/
//    idwt(wt, out);// Perform IDWT (if needed)
//// Test Reconstruction
//    for (i = 0; i < wt->siglength; ++i) {
//        diff[i] = out[i] - inp[i];
//    }
//    printf("\n\n%d\n\n", wt->siglength);
//    free(wavData->data);
//    wavData->data = out;
//    printf("\n MAX %g \n",absmax(diff, wt->siglength)); // If Reconstruction succeeded then the output should be a small value.
//    wt_summary(wt);// Prints the full summary.
//    wave_free(obj);
//    wt_free(wt);
//    free(inp);
//    free(out);
//    free(diff);
//    return 0;
//}
