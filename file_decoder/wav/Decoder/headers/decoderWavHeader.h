//
// Created by Alexandre Josien on 23/04/2021.
//

#ifndef SOUNDHOOK_DECODERWAVHEADER_H
#define SOUNDHOOK_DECODERWAVHEADER_H

#include "../../types/wav.h"
#include "stdio.h"

WavHeader* decodeWavHeader(FILE* f);

#endif //SOUNDHOOK_DECODERWAVHEADER_H
