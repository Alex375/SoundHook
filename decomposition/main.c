//
// Created by Noé Bonne on 3/11/21.
//
#include <stdio.h>
#include "../file_decoder/wav/wav.h"
#include "../file_decoder/wav/Decoder/WavDecoder.h"
#include "../file_decoder/wav/WavTools.h"

#include "fft.h"

#define FILE_PATH "/Users/alexandrejosien/Desktop/SoundHook/file_decoder/sounds/demomac.wav"

int main(){
    printf("====Starting decoding====\n");
    FILE * f = openFile(FILE_PATH);
    WavData * data = decodeWave(f);
    printWavHeader(data->header);
    printf("====File decoded====\n");
    fclose(f);
    printf("====Starting decomposition====\n");
    fft(data->data, (int)data->header->num_of_sample, (double)data->header->overall_size/ (double)data->header->byterate, FILE_PATH);
    printf("====Decomposition done====\n");
    freeWavData(data);
}
