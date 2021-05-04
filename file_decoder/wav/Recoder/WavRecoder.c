//
// Created by Alexandre Josien on 31/03/2021.
//

#include "headers/WavRecoder.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/wav.h"
#include "../tools/headers/WavTools.h"
#include "../tools/headers/WavChecker.h"



int recodeHeaderRiffChunk(WavHeader* data, FILE* f)
{
    fwriteHand(data->riff, 4, 1, f);
    fwriteHand(&(data->overall_size), 4, 1, f);
    fwriteHand(data->wave, 4, 1, f);
    return 0;
}

int recodeHeaderFormatChunk(WavHeader* data, FILE* f)
{
    fwriteHand(data->fmt_chunk_marker, 4, 1, f);
    fwriteHand(&(data->length_of_fmt), 4, 1, f);
    unsigned short temp = (unsigned short)(data->format_type);
    fwriteHand(&temp, 2, 1, f);
    unsigned short temp2 = (unsigned short)(data->channels);
    fwriteHand(&temp2, 2, 1, f);
    fwriteHand(&(data->sample_rate), 4, 1, f);
    fwriteHand(&(data->byterate), 4, 1, f);
    unsigned short temp3 = (unsigned short)(data->block_align);
    fwriteHand(&temp3, 2, 1, f);
    unsigned short temp4 = (unsigned short)(data->bits_per_sample);
    fwriteHand(&temp4, 2, 1, f);
    fwriteHand(data->data_chunk_header, 4, 1, f);
    fwriteHand(&(data->data_size), 4, 1, f);

    return 0;
}

int recodeData(WavData* fileData, FILE* f)
{
    for (unsigned long i = 0; i < fileData->addInfo->num_of_sample; i++)
    {
        int data = fileData->data[i];
        short temp;
        switch (fileData->addInfo->byte_in_channel) {
            case 1:
                data += 128;
                fwriteHand(&data, 1, 1, f);
                break;
            case 2:
                temp = data;
                fwriteHand(&temp, 2, 1, f);
                break;
            case 3:
                if (data < 0)
                {
                    data ^= 0xffffffff;
                    data += 1;
                    data ^= 0x00ffffff;
                    data += 1;
                    data &= 0x00ffffff;
                }
                fwriteHand(&data, 3, 1, f);
                break;
            case 4:
                fwriteHand(&data, 4, 1, f);
                break;
        }
    }
    return 0;
}

void recodeInfoChunk(InfoChunk* info, FILE* f)
{
    if (info->size == 0 || info->data == NULL)
        return;
    fwriteHand(info->data, info->size, 1, f);
}

void recodeWav(int* data, FILE* or, long size)
{

    char* header = malloc(44 * sizeof (char ));
    fread(header, sizeof (char ) * 44, 1, or);
    FILE* fp = fopen("corrected.wav", "w");
    fwrite(header, sizeof (char) * 44, 1, fp);
    for (long i = 0; i < size; i++)
    {
        int dataR = ((data[i] & 0xff000000) >> 24) |
               ((data[i] & 0x00ff0000) >> 8) |
               ((data[i] & 0x0000ff00) << 8) |
               ((data[i] & 0x000000ff) << 24);
        fwrite(&data[i], sizeof (int), 1, fp);
    }
    fclose(fp);
}

int wavRecoder(WavData* data, char* path)
{
    FILE* f = openNewFile(path);

    recodeHeaderRiffChunk(data->header, f);
    recodeHeaderFormatChunk(data->header, f);
    recodeData(data, f);
    //recodeInfoChunk(data->infoChunk, f);
    fclose(f);

    return 0;

}