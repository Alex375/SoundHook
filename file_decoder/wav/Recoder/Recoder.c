//
// Created by Alexandre Josien on 31/03/2021.
//

#include "headers/Recoder.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types/wav.h"
#include "../tools/headers/WavTools.h"
#include "../tools/headers/WavChecker.h"


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

