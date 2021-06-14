//
// Created by Alexandre Josien on 14/06/2021.
//

#ifndef SOUNDHOOK_SOUNDPLAY_H
#define SOUNDHOOK_SOUNDPLAY_H
#include "../../type/types.h"

void stopSoundOld(UIData* data);
void stopSoundNew(UIData* data);
void* playSoundOld(void* arg);
void* playSoundNew(void* arg);

#endif //SOUNDHOOK_SOUNDPLAY_H
