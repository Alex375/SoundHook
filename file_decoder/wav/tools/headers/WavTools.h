//
// Created by Alexandre Josien on 30/03/2021.
//

#ifndef SOUNDHOOK_WAVTOOLS_H
#define SOUNDHOOK_WAVTOOLS_H

#include <stdio.h>
#include "../../types/wav.h"

unsigned int littleEndianToBigEndian4(unsigned char* buff);
unsigned int littleEndianToBigEndian2(unsigned char buff[2]);
void freeWavData(WavData* data);
FILE* openFile(const char* file);
FILE* openNewFile(const char* file);
void freadHand(void* ptr, size_t size, size_t nbitem, FILE* file);
void fwriteHand(void* ptr, size_t size, size_t nbitem, FILE* file);
void printAttS(const char * name, unsigned char* value);
void printAttI(const char * name, int value);
void printWavHeader(WavHeader* header);

#endif //SOUNDHOOK_WAVTOOLS_H
