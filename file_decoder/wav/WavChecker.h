//
// Created by Alexandre Josien on 30/03/2021.
//

#ifndef SOUNDHOOK_WAVCHECKER_H
#define SOUNDHOOK_WAVCHECKER_H

#include "wav.h"
#include <stdio.h>

int checkHeader(WavHeader* header, FILE* f);
int checkRiff(WavHeader* h);


#endif //SOUNDHOOK_WAVCHECKER_H
