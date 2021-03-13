//
// Created by Alexandre Josien on 10/03/2021.
//

#ifndef SOUNDHOOK_DECODER_H
#define SOUNDHOOK_DECODER_H
#include "wav.h"
#include <stdio.h>

WavHeader* decodeWavHeader(FILE* f);
void printWavHeader(WavHeader* header);
int checkHeader(WavHeader* header, FILE* f);
FILE* openFile(const char* file);


#endif //SOUNDHOOK_DECODER_H
