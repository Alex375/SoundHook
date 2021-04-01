//
// Created by Noé Bonne on 3/11/21.
//
#include <stdio.h>
#include "../file_decoder/wav/wav.h"
#include "../file_decoder/wav/Decoder/WavDecoder.h"
#include "../file_decoder/wav/WavTools.h"

#include "fft.h"

#define FILE_PATH "/Users/noway/Desktop/S4-Project/SoundHook/file_decoder/sounds/livecodenoise.wav"

int main(){
    printf("decomposition of your fat mom\n");
    FILE * f = openFile(FILE_PATH);
    WavData * data = decodeWave(f);
    fclose(f);
    printWavHeader(data->header);
    for(int i = 0; i < data->header->num_of_sample; i++)
    {
        //printf("%i -> %i\n", i, data->data[i]);
    }
    fft(data->data, (int)data->header->num_of_sample, (double)data->header->overall_size/ (double)data->header->byterate, FILE_PATH);
}
