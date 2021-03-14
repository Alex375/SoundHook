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


const size_t BUFFER_SIZE = 1024;


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

WavHeader* decodeWavHeader(FILE* f)
{
    unsigned char* buff4 = malloc(sizeof (char) * 4);
    unsigned char* buff2 = malloc(sizeof (char) * 2);
    WavHeader* header = malloc(sizeof (WavHeader));


    int status =0;

    status = fread(header->riff, sizeof (header->riff), 1, f);
    status = fread(buff4, sizeof (char) * 4, 1, f);
    header->overall_size = littleEndianToBigEndian4(buff4);

    status = fread(header->wave, sizeof (header->wave), 1, f);
    status = fread(header->fmt_chunk_marker, sizeof (header->fmt_chunk_marker), 1, f);
    status = fread(buff4, sizeof (char ) * 4, 1, f);
    header->length_of_fmt = littleEndianToBigEndian4(buff4);
    status = fread(buff2, sizeof (char) * 2, 1, f);
    header->format_type = littleEndianToBigEndian2(buff2);
    status = fread(buff2, sizeof (char) * 2, 1, f);
    header->channels = littleEndianToBigEndian2(buff2);
    status = fread(buff4, sizeof (char) * 4, 1, f);
    unsigned int temp = littleEndianToBigEndian4(buff4);
    header->sample_rate = littleEndianToBigEndian4(buff4);
    status = fread(buff4, sizeof (char) * 4, 1, f);
    header->byterate = littleEndianToBigEndian4(buff4);
    status = fread(buff2, sizeof (char) * 2, 1, f);
    header->block_align = littleEndianToBigEndian2(buff2);
    status = fread(buff2, sizeof (char) * 2, 1, f);
    header->bits_per_sample = littleEndianToBigEndian2(buff2);
    status = fread(header->data_chunk_header, sizeof (header->data_chunk_header), 1, f);
    status = fread(buff4, sizeof (char) * 4, 1, f);
    header->data_size = littleEndianToBigEndian4(buff4);

    return header;
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
    printf("Overall size -> %x bytes %u kb\n", header->overall_size, header->overall_size/1024);
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
    printf("Number of sample -> %lu\n", header->num_of_sample);
    printf("Approx duration -> %f s \n",  (float)(header->overall_size) / (float)(header->byterate));


}


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
    long low_limit = 0;
    long high_limit = 0;
    switch (header->bits_per_sample) {
        case 8:
            low_limit = -128;
            high_limit = 127;
            break;
        case 16:
            low_limit = -32768;
            high_limit = 32767;
            break;
        case 32:
            low_limit = -2147483648;
            high_limit = 2147483647;
            break;
        default:
            printf("Bit per sample error.\n");
            return 6;
    }

    char data_buffer[sample_size];
    int status = 0;
    for (unsigned long i = 0; i < header->num_of_sample; i++)
    {
        status = fread(data_buffer, sizeof (char) * sample_size, 1, f);
        if (status != 1)
        {
            printf("Error while reading data.\n");
            return 7;
        }

        for (unsigned int chan = 0; chan < header->channels; chan++)
        {
            int data = 0;
            switch (byte_in_channel) {
                case 1:
                    data = data_buffer[chan * byte_in_channel] & 0x00ff;
                    data -= 128;
                    break;
                case 2:
                    data = (data_buffer[chan * byte_in_channel] & 0x00ff) |
                            (data_buffer[chan * byte_in_channel + 1]<<8);
                    break;
                case 4:
                    data = (data_buffer[chan * byte_in_channel] & 0x00ff) |
                            (data_buffer[chan * byte_in_channel + 1] & 0x00ff << 8) |
                            (data_buffer[chan * byte_in_channel + 2] & 0x00ff << 16) |
                            (data_buffer[chan * byte_in_channel + 3] & 0x00ff << 24);
                    break;
                default:
                    err(1, "Byte in channel error");
            }
            if (data < low_limit || data > high_limit)
            {
                printf("Value out of range at sample %lu, channel %i\n", i, chan);
                return 8;
            }
            printf("Data sample %lu chan %u ->  %f  -> %i\n", i, chan, (float)(data) / high_limit, data);

        }
    }

    return 0;
}
