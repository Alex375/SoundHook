//
// Created by Alexandre Josien on 30/03/2021.
//

#include "headers/WavTools.h"
#include "../types/wav.h"
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>

void freeWavData(WavData* data)
{
    free(data->header);
    free(data->data);
    free(data->addInfo);
    if (data->infoChunk->data != NULL)
        free(data->infoChunk->data);
    free(data->infoChunk);
    free(data);
}

unsigned int littleEndianToBigEndian4(unsigned char* buff)
{
    return buff[0] | (buff[1]<<8) | (buff[2]<<16) | (buff[3]<<28);
}

unsigned int littleEndianToBigEndian2(unsigned char buff[2])
{
    return buff[0] | (buff[1] << 8);
}

FILE* openFile(const char* file)
{
    FILE* f = fopen(file, "rb");
    if (f == NULL)
        err(1, "Unable to open file");
    return f;
}

FILE* openNewFile(const char* file)
{
    FILE* f = fopen(file, "w+");
    if (f == NULL)
        err(EXIT_FAILURE, "Unable to open new file");
    return f;
}

void freadHand(void* ptr, size_t size, size_t nbitem, FILE* file)
{
    size_t res = fread(ptr, size, nbitem, file);
    if (res != nbitem)
        err(EXIT_FAILURE, "Failed to read or read full length.");
}

void fwriteHand(void* ptr, size_t size, size_t nbitem, FILE* file)
{
    size_t res = fwrite(ptr, size, nbitem, file);
    if (res != nbitem)
        err(EXIT_FAILURE, "Failed to write or write full length.");
}

void printAttI(const char * name, int value)
{
    printf("%s -> %u\n", name, value);
}


void printAttS(const char * name, unsigned char* value)
{
    printf("%s -> %.4s\n", name, value);
}

void printWavHeader(WavHeader* header)
{
    printf("===== Wav Header =====\n\n");
    printAttS("RIFF", header->riff);
    printf("Overall size -> %u bytes %u kb\n", header->overall_size, header->overall_size/1024);
    printAttS("Wav marker", header->wave);
    printAttS("Fmt marker", header->fmt_chunk_marker);
    printAttI("Fmt header length", header->length_of_fmt);
    char fmt[10] = "";
    switch (header->format_type) {
        case 1:
            strcpy(fmt, "PCM");
            break;
        case 6:
            strcpy(fmt, "A-law");
            break;
        case 7:
            strcpy(fmt, "Mu-law");
            break;
    }

    printf("Format type -> %u, (%s)\n", header->format_type, fmt);
    printAttI("Channels", header->channels);
    printAttI("Sample rate", header->sample_rate);
    printAttI("Byte rate", header->byterate);
    printAttI("Bit rate", header->byterate * 8);
    printAttI("Block alignment", header->block_align);
    printAttI("Bits per sample", header->bits_per_sample);
    printAttS("Data chunk marker", header->data_chunk_header);
    printAttI("Data chunk size", header->data_size);
    printf("Approx duration -> %f s \n",  (float)(header->data_size) / (float)(header->byterate));


}
