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
#include "wav.h"


const size_t BUFFER_SIZE = 1024;

char* charToBuff(const char * s, char* buff, size_t* len)
{
    char* temp = buff;
    *len  = 0;
    while(*s != '\0')
    {
        *temp = *s;
        temp++;
        s++;
        *len++;
    }
    return buff;
}

void decode(const char* path)
{
    char* buffer = calloc(1024, sizeof (char));
    int fd = open(path, O_RDONLY);
    if(fd == -1)
        err(1, "Unable to open file");


    read(fd, buffer, 4);
    printf("ChunkID : \n");
    write(STDOUT_FILENO, buffer, 4);
    printf("\n");

    size_t r = read(fd, buffer, 4);
    printf("Chunk size : \n");
    char temp0 = buffer[0];
    char temp1 = buffer[1];
    buffer[0] = buffer[3];
    buffer[1] = buffer[2];
    buffer[2] = temp1;
    buffer[3] = temp0;
    size_t w = write(STDOUT_FILENO, buffer, 4);
    printf("\n");


}

unsigned int littleEndianToBigEndian4(char buff[4])
{
    return buff[0] | (buff[1] << 8) | (buff[2] << 16) | (buff[3] << 28);
}

unsigned int littleEndianToBigEndian2(char buff[2])
{
    return buff[0] | (buff[1] << 8);
}

WavHeader* decodeWavHeader(const char* file)
{
    unsigned char buff4[4];
    unsigned char buff2[2];
    int fd;
    WavHeader header;
    FILE* f = fopen(file, "rb");
    if (f == NULL)
        err(1, "Unable to open file");

    int status =0;

    status = fread(header.riff, sizeof (header.riff), 1, f);
    status = fread(buff4, sizeof (buff4), 1, f);
    header.overall_size = littleEndianToBigEndian4(buff4);
    status = fread(header.wave, sizeof (header.wave), 1, f);
    status = fread(header.fmt_chunk_marker, sizeof (header.fmt_chunk_marker), 1, f);
    status = fread(buff4, sizeof (buff4), 1, f);
    header.length_of_fmt = littleEndianToBigEndian4(buff4);
    status = fread(buff2, sizeof (buff2), 1, f);
    

}


