//
// Created by Alexandre Josien on 05/03/2021.
//
#include<stdio.h>

int main()
{
    char c = (char)205;

    printf("Signed -> %x %x - %lu\n", c, (char) (c & 0x00ff), sizeof(char));

    unsigned char uc = 205;

    printf("Unsigned -> %x %x - %lu\n", uc, (char) (uc & 0x00ff), sizeof(unsigned char));
}
