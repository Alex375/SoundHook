//
// Created by Alexandre Josien on 23/04/2021.
//

#include "types.h"
#include "../../file_decoder/wav/tools/headers/WavTools.h"


void safeFree(void* p)
{
    if (p != NULL)
        free(p);
}

void freeUiData(UIData* data)
{
    safeFree(data->soundPathOld);
    safeFree(data->soundPathNew);
    if (data->soundData != NULL)
        freeWavData(data->soundData);
    safeFree(data->equalizerValue);
}