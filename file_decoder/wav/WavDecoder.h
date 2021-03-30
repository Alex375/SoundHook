//
// Created by Alexandre Josien on 30/03/2021.
//

#ifndef SOUNDHOOK_WAVDECODER_H
#define SOUNDHOOK_WAVDECODER_H
#include "wav.h"
#include "stdio.h"

WavHeader* decodeWavHeader(FILE* f);
int* decodeData(FILE* f, WavHeader* header, int* res);
WavData * decodeWave(FILE* f);

#endif //SOUNDHOOK_WAVDECODER_H
