//
// Created by Alexandre Josien on 30/03/2021.
//

#include "WavChecker.h"
#include "wav.h"
#include <stdio.h>
#include <err.h>



int checkHeader(WavHeader* header, FILE* f)
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
    header->num_of_sample = (8 * header->data_size) / (header->channels * header->bits_per_sample);
    long sample_size = (header->channels * header->bits_per_sample) / 8;
    long byte_in_channel = sample_size / header->channels;
    if(byte_in_channel * header->channels != sample_size)
    {
        printf("Sample size error.\n");
        return 5;
    }

    return 0;
}
