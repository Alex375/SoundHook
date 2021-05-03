//
// Created by Alexandre Josien on 23/04/2021.
//

#include "headers/decoderWavHeader.h"
#include "../types/wav.h"
#include <stdio.h>
#include <stdlib.h>
#include "../tools/headers/WavChecker.h"
#include "../tools/headers/WavTools.h"
#include <err.h>

int decodeWavHeaderRIFFChunk(FILE* f, WavHeader* header);
int decodeWavHeaderFormatChunk(FILE* f, WavHeader* header);


WavHeader* decodeWavHeader(FILE* f)
{
    WavHeader* header = malloc(sizeof (WavHeader));
    if (header == NULL)
        err(EXIT_FAILURE, "Memory allocation failed");
    if (decodeWavHeaderRIFFChunk(f, header) == -1 || decodeWavHeaderFormatChunk(f, header) == -1)
        return NULL;
    return header;
}

int decodeWavHeaderRIFFChunk(FILE* f, WavHeader* header)
{
    unsigned char* buff4 = malloc(sizeof (char) * 4);

    freadHand(header->riff, sizeof (header->riff), 1, f);
    if(!checkMarker(header->riff, "RIFF"))
        return -1;

    freadHand(buff4, sizeof (char) * 4, 1, f);
    header->overall_size = littleEndianToBigEndian4(buff4);

    freadHand(header->wave, sizeof (header->wave), 1, f);
    if(! checkMarker(header->wave, "WAVE"))
        return -1;
    return 0;
}

int decodeWavHeaderFormatChunk(FILE* f, WavHeader* header)
{
    unsigned char* buff4 = malloc(sizeof (char) * 4);
    unsigned char* buff2 = malloc(sizeof (char) * 2);

    freadHand(header->fmt_chunk_marker, sizeof (header->fmt_chunk_marker), 1, f);
    header->fmt_chunk_marker[3] = '\0';
    if(! checkMarker(header->fmt_chunk_marker, "fmt"))
        return -1;
    freadHand(buff4, sizeof (char ) * 4, 1, f);
    header->length_of_fmt = littleEndianToBigEndian4(buff4);
    if(header->length_of_fmt != 16)
        return -1;
    freadHand(buff2, sizeof (char) * 2, 1, f);
    header->format_type = littleEndianToBigEndian2(buff2);
    if(header->format_type != 1)
        return -1;
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

    return 0;
}