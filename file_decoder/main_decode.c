//
// Created by Alexandre Josien on 10/03/2021.
//

#include "wav/WavDecoder.h"
#include "wav/wav.h"
#include<stdio.h>
#include <stdio.h>
#include "WavTools.h"
#include "wav/WavChecker.h"
/*
int main()
{
    FILE* f = openFile("/Users/alexandrejosien/Desktop/SoundHook/file_decoder/sounds/testsin24.wav");
    WavData * data = decodeWave(f);
    printf("%i\n", checkHeader(data->header));
    for(size_t i = 0; i < data->header->num_of_sample; i++)
    {
        printf("%zu->%i\n", i, data->data[i]);
    }

    return 0;
}
*/