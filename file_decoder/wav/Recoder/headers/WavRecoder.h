//
// Created by Alexandre Josien on 31/03/2021.
//

#ifndef SOUNDHOOK_WAVRECODER_H
#define SOUNDHOOK_WAVRECODER_H

#include <stdio.h>
#include "../../types/wav.h"

int wavRecoder(WavData* data, char* path);
void recodeWav(int* data, FILE* or, long size);

#endif //SOUNDHOOK_WAVRECODER_H
