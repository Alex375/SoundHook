//
// Created by Alexandre Josien on 10/03/2021.
//
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"
#include "WavTools.h"




WavHeader* decodeWavHeader(FILE* f)
{
    unsigned char* buff4 = malloc(sizeof (char) * 4);
    unsigned char* buff2 = malloc(sizeof (char) * 2);
    WavHeader* header = malloc(sizeof (WavHeader));


    int status = 0;

    freadHand(header->riff, sizeof (header->riff), 1, f);
    freadHand(buff4, sizeof (char) * 4, 1, f);
    header->overall_size = littleEndianToBigEndian4(buff4);

    freadHand(header->wave, sizeof (header->wave), 1, f);
    freadHand(header->fmt_chunk_marker, sizeof (header->fmt_chunk_marker), 1, f);
    freadHand(buff4, sizeof (char ) * 4, 1, f);
    header->length_of_fmt = littleEndianToBigEndian4(buff4);
    freadHand(buff2, sizeof (char) * 2, 1, f);
    header->format_type = littleEndianToBigEndian2(buff2);
    freadHand(buff2, sizeof (char) * 2, 1, f);
    header->channels = littleEndianToBigEndian2(buff2);
    freadHand(buff4, sizeof (char) * 4, 1, f);
    header->sample_rate = littleEndianToBigEndian4(buff4);
    freadHand(buff4, sizeof (char) * 4, 1, f);
    header->byterate = littleEndianToBigEndian4(buff4);
    freadHand(buff2, sizeof (char) * 2, 1, f);
    header->block_align = littleEndianToBigEndian2(buff2);
    freadHand(buff2, sizeof (char) * 2, 1, f);
    header->bits_per_sample = littleEndianToBigEndian2(buff2);
    freadHand(header->data_chunk_header, sizeof (header->data_chunk_header), 1, f);
    freadHand(buff4, sizeof (char) * 4, 1, f);
    header->data_size = littleEndianToBigEndian4(buff4);

    return header;
}



