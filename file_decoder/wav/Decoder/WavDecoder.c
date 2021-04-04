//
// Created by Alexandre Josien on 10/03/2021.
//
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../wav.h"
#include "../WavTools.h"
#include "../WavChecker.h"




WavHeader* decodeWavHeader(FILE* f)
{
    unsigned char* buff4 = malloc(sizeof (char) * 4);
    unsigned char* buff2 = malloc(sizeof (char) * 2);
    WavHeader* header = malloc(sizeof (WavHeader));


    int status = 0;

    freadHand(header->riff, sizeof (header->riff), 1, f);
    if(! checkMarker(header->riff, "RIFF"))
        return NULL;

    freadHand(buff4, sizeof (char) * 4, 1, f);
    header->overall_size = littleEndianToBigEndian4(buff4);

    freadHand(header->wave, sizeof (header->wave), 1, f);
    if(! checkMarker(header->wave, "WAVE"))
        return NULL;
    freadHand(header->fmt_chunk_marker, sizeof (header->fmt_chunk_marker), 1, f);
    header->fmt_chunk_marker[3] = '\0';
    if(! checkMarker(header->fmt_chunk_marker, "fmt"))
        return NULL;
    freadHand(buff4, sizeof (char ) * 4, 1, f);
    header->length_of_fmt = littleEndianToBigEndian4(buff4);
    if(header->length_of_fmt != 16)
        return NULL;
    freadHand(buff2, sizeof (char) * 2, 1, f);
    header->format_type = littleEndianToBigEndian2(buff2);
    if(header->format_type != 1)
        return NULL;
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

int* decodeData(FILE* f, WavHeader* header)
{
    header->num_of_sample = (8 * header->data_size) / (header->channels * header->bits_per_sample);
    int * res = malloc(sizeof (int) * header->num_of_sample * header->channels);
    if (res == NULL)
        err(EXIT_FAILURE, "Malloc failed.");
    long sample_size = (header->channels * header->bits_per_sample) / 8;
    long byte_in_channel = sample_size / header->channels;
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
        case 24:
            low_limit = -8388608;
            high_limit = 8388607;
            break;
        case 32:
            low_limit = -2147483648;
            high_limit = 2147483647;
            break;
        default:
            err(EXIT_FAILURE, "Byte per sample error.");
    }

    char data_buffer[sample_size];
    int status = 0;
    for (unsigned long i = 0; i < header->num_of_sample; i++)
    {
        status = fread(data_buffer, sizeof (char) * sample_size, 1, f);
        if (status != 1)
        {
            printf("Error while reading data.\n");
            return NULL;
        }

        int data = 0;
        for (unsigned int chan = 0; chan < header->channels; chan++)
        {
            data = 0;
            short temp;
            switch (byte_in_channel) {
                case 1:
                    data = data_buffer[chan * byte_in_channel] & 0x00ff;
                    data -= 128;
                    break;
                case 2:
                    temp = (data_buffer[chan * byte_in_channel] & 0x00ff) |
                                 ((data_buffer[chan * byte_in_channel + 1] & 0x00ff)<<8);
                    data = temp;
                    break;
                case 3 :
                    data = ((data_buffer[chan * byte_in_channel] & 0x00ff) |
                            ((data_buffer[chan * byte_in_channel + 1] & 0x00ff) << 8) |
                            ((data_buffer[chan * byte_in_channel + 2] & 0x00ff) << 16));
                    if (data > high_limit)
                    {
                        data ^= 0x00ffffff;
                        data += 1;
                        data = data & 0x00ffffff;
                        data ^= 0xffffffff;
                        data += 1;
                    }
                    break;
                case 4:
                    data = (data_buffer[chan * byte_in_channel] & 0x00ff) |
                           ((data_buffer[chan * byte_in_channel + 1] & 0x00ff) << 8) |
                           ((data_buffer[chan * byte_in_channel + 2] & 0x00ff) << 16) |
                           ((data_buffer[chan * byte_in_channel + 3] & 0x00ff) << 24);
                    break;
                default:
                    err(1, "Byte in channel error");
            }

            if (data < low_limit || data > high_limit)
            {
                printf("Value out of range at sample %lu, channel %i\n", i, chan);
                return NULL;
            }
            //printf("Data sample %lu chan %u -> %f -> %i\n", i, chan, (float)(data) / (float)(high_limit), data);
            res[i + chan] = data;

        }
    }
    return res;

}

WavData * decodeWave(FILE* f)
{
    WavData* data = malloc(sizeof (WavData));
    if (data == NULL)
        perror("Malloc failed");
    data->header = decodeWavHeader(f);
    if (data->header == NULL)
        err(EXIT_FAILURE, "Header decoding failed check format.");
    data->data = decodeData(f, data->header);
    if(data->data == NULL)
        err(EXIT_FAILURE, "Data decoding failed check data.");
    if (checkHeader(data->header) != 0)
        err(EXIT_FAILURE, "Header checking failed.");
    return data;
}