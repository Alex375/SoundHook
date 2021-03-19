//
// Created by Alexandre Josien on 10/03/2021.
//
#include "decoder.h"
#include "wav.h"
#include<stdio.h>

int main()
{
    FILE* f = openFile("/Users/bozecaurore/Desktop/#EPITA/S4/PROJET/SoundHook/file_decoder/square.wav");
    WavHeader * header = decodeWavHeader(f);
    printf("%i\n", checkHeader(header, f));
    printWavHeader(header);

    return 0;
}
