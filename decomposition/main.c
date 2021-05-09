/*
//Created by Noé Bonne on 3/11/21.

#include <stdio.h>
#include <stdlib.h>
#include "../file_decoder/wav/types/wav.h"
#include "../file_decoder/wav/Decoder/headers/WavDecoder.h"

#include "fft.h"
#include "../file_decoder/wav/tools/headers/WavTools.h"

#define FILE_PATH "/Users/noway/Desktop/S4-Project/SoundHook/sounds/testlowamp.wav"

int main(){
    printf("====Starting decoding====\n");
    FILE * f = openFile(FILE_PATH);
    WavData * data = decodeWave(FILE_PATH);
    printWavHeader(data->header);
    printf("====File decoded====\n");
    fclose(f);
    printf("====Starting decomposition====\n");
    int SVlen = 5;
    double * sliderValues = malloc(sizeof(double) * SVlen);
    for (int i = 0; i < SVlen; ++i) {
        sliderValues[i] = 1;
    }

    fft(data->data, (int)data->addInfo->num_of_sample, (double)data->header->overall_size/ (double)data->header->byterate, FILE_PATH, sliderValues, SVlen, "EH");
    printf("====Decomposition done====\n");
    freeWavData(data);
}
*/