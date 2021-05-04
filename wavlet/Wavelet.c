//
// Created by Alexandre Josien on 04/05/2021.
//

#include "headers/Wavelet.h"
#include "../file_decoder/wav/types/wav.h"
#include "../file_decoder/wav/tools/headers/WavTools.h"


//Do not change function prototype
void wavelet(WavData* wavData)
{
    printWavHeader(wavData->header);
}