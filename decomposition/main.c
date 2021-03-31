//
// Created by Noé Bonne on 3/11/21.
//
#include <stdio.h>
#include "/usr/local/Cellar/fftw/3.3.9/include/fftw3.h"
#include "../file_decoder/wav/wav.h"
#include "../file_decoder/wav/Decoder/WavDecoder.h"
#include "../file_decoder/wav/WavTools.h"

#include "fft.h"

int main(){
    int a = 8;
    printf("decomposition of your fat mom\n");
    FILE * f = openFile("/Users/alexandrejosien/Desktop/SoundHook/file_decoder/sounds/testlowamp.wav");
    WavData * data = decodeWave(f);
    fclose(f);
    printWavHeader(data->header);
    for(int i = 0; i < data->header->num_of_sample; i++)
    {
        //printf("%i -> %i\n", i, data->data[i]);
    }
    fft(data->data, data->header->num_of_sample, (double)data->header->overall_size/ (double)data->header->byterate);
}
