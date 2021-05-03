//
// Created by Alexandre Josien on 30/03/2021.
//

#include "headers/WavChecker.h"
#include "../types/wav.h"
#include <stdio.h>
#include <err.h>

int checkMarker(unsigned char test[4], const char * ref)
{
    for (size_t i = 0; i < 4; i++)
    {
        if (test[i] != ref[i])
        {
            return 0;
        }
    }
    return 1;
}



int checkHeader(WavHeader* header)
{
    if (header->format_type != 1 && header->format_type != 3 && header->format_type != 6 && header->format_type != 7)
    {
        printf("Format type error.\n");
        return 1;
    }
    if (header->byterate != header->sample_rate * header->channels * (header->bits_per_sample / 8))
    {
        printf("Byterate error.\n");
        return 2;
    }
    if (header->block_align !=  header->channels * (header->bits_per_sample / 8))
    {
        printf("Blockalling error.\n");
        return 3;
    }
    if (header->bits_per_sample == 0 || header->bits_per_sample % 8 != 0)
    {
        printf("Bit per sample error.\n");
        return 4;
    }
    long sample_size = (header->channels * header->bits_per_sample) / 8;
    long byte_in_channel = sample_size / header->channels;
    if(byte_in_channel * header->channels != sample_size)
    {
        printf("Sample size error.\n");
        return 5;
    }

    return 0;
}
