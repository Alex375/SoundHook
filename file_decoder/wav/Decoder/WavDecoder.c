//
// Created by Alexandre Josien on 10/03/2021.
//
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/wav.h"
#include "../tools/headers/WavTools.h"
#include "../tools/headers/WavChecker.h"
#include "headers/decoderWavHeader.h"



WavAddInfo* getWavAddInfo(WavHeader* header)
{
    WavAddInfo* info = malloc(sizeof (WavAddInfo));
    if (info == NULL)
        err(EXIT_FAILURE, "Memory allocation failed");

    info->num_of_sample = (8 * header->data_size) / (header->channels * header->bits_per_sample);
    info->sample_size = (header->channels * header->bits_per_sample) / 8;
    info->byte_in_channel = info->sample_size / header->channels;
    info->time = (float)(header->data_size) / (float)(header->byterate);
    switch (header->bits_per_sample) {
        case 8:
            info->low_limit = -128;
            info->high_limit = 127;
            break;
        case 16:
            info->low_limit = -32768;
            info->high_limit = 32767;
            break;
        case 24:
            info->low_limit = -8388608;
            info->high_limit = 8388607;
            break;
        case 32:
            info->low_limit = -2147483648;
            info->high_limit = 2147483647;
            break;
        default:
            err(EXIT_FAILURE, "Byte per sample error.");
    }
    return info;
}


int* decodeData(FILE* f, WavHeader* header, WavAddInfo* info)
{
    int * res = malloc(sizeof (int) * info->num_of_sample * header->channels);
    if (res == NULL)
        err(EXIT_FAILURE, "Malloc failed.");

    char data_buffer[info->sample_size];
    int status = 0;
    for (unsigned long i = 0; i < info->num_of_sample; i++)
    {
        status = fread(data_buffer, sizeof (char) * info->sample_size, 1, f);
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
            switch (info->byte_in_channel) {
                case 1:
                    data = data_buffer[chan * info->byte_in_channel] & 0x00ff;
                    data -= 128;
                    break;
                case 2:
                    temp = (data_buffer[chan * info->byte_in_channel] & 0x00ff) |
                                 ((data_buffer[chan * info->byte_in_channel + 1] & 0x00ff)<<8);
                    data = temp;
                    break;
                case 3 :
                    data = ((data_buffer[chan * info->byte_in_channel] & 0x00ff) |
                            ((data_buffer[chan * info->byte_in_channel + 1] & 0x00ff) << 8) |
                            ((data_buffer[chan * info->byte_in_channel + 2] & 0x00ff) << 16));
                    if (data > info->high_limit)
                    {
                        data ^= 0x00ffffff;
                        data += 1;
                        data = data & 0x00ffffff;
                        data ^= 0xffffffff;
                        data += 1;
                    }
                    break;
                case 4:
                    data = (data_buffer[chan * info->byte_in_channel] & 0x00ff) |
                           ((data_buffer[chan * info->byte_in_channel + 1] & 0x00ff) << 8) |
                           ((data_buffer[chan * info->byte_in_channel + 2] & 0x00ff) << 16) |
                           ((data_buffer[chan * info->byte_in_channel + 3] & 0x00ff) << 24);
                    break;
                default:
                    err(1, "Byte in channel error");
            }

            if (data < info->low_limit || data > info->high_limit)
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


WavData * decodeWave(char* filePath)
{
    if (filePath== NULL)
        err(EXIT_FAILURE, "No file passed");
    FILE* f = openFile(filePath);
    WavData* data = malloc(sizeof (WavData));
    if (data == NULL)
        perror("Malloc failed");

    data->header = decodeWavHeader(f);
    if (data->header == NULL)
        err(EXIT_FAILURE, "Header decoding failed check format.");

    data->addInfo = getWavAddInfo(data->header);

    data->data = decodeData(f, data->header, data->addInfo);
    if(data->data == NULL)
        err(EXIT_FAILURE, "Data decoding failed check data.");
    if (checkHeader(data->header) != 0)
        err(EXIT_FAILURE, "Header checking failed.");
    fclose(f);
    return data;
}