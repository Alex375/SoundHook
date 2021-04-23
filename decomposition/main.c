//
// Created by Noé Bonne on 3/11/21.
//
#include <stdio.h>
#include "../file_decoder/wav/types/wav.h"
#include "../file_decoder/wav/Decoder/headers/WavDecoder.h"
#include "../file_decoder/wav/tools/headers/WavTools.h"

#include "fft.h"

#define FILE_PATH "/Users/alexandrejosien/Desktop/SoundHook/sounds/demomac.wav"

int main(){
    printf("====Starting decoding====\n");
    FILE * f = openFile(FILE_PATH);
    WavData * data = decodeWave(f);
    printWavHeader(data->header);
    printf("====File decoded====\n");
    fclose(f);
    printf("====Starting decomposition====\n");
    fft(data->data, (int)data->addInfo->num_of_sample, (double)data->header->overall_size/ (double)data->header->byterate, FILE_PATH);
    printf("====Decomposition done====\n");
    freeWavData(data);
}
