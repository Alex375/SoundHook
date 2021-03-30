//
// Created by Alexandre Josien on 10/03/2021.
//

#ifndef SOUNDHOOK_WAVDECODER_H
#define SOUNDHOOK_WAVDECODER_H
#include "wav/wav.h"
#include <stdio.h>

WavHeader* decodeWavHeader(FILE* f);
void printWavHeader(WavHeader* header);
int checkHeader(WavHeader* header, FILE* f);
FILE* openFile(const char* file);


#endif //SOUNDHOOK_WAVDECODER_H
