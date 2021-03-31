//
// Created by Alexandre Josien on 30/03/2021.
//

#ifndef SOUNDHOOK_WAVCHECKER_H
#define SOUNDHOOK_WAVCHECKER_H

#include "wav.h"
#include <stdio.h>

int checkMarker(unsigned char test[4], const char * ref);
int checkHeader(WavHeader* header);


#endif //SOUNDHOOK_WAVCHECKER_H
