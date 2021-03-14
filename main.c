//
// Created by Alexandre Josien on 05/03/2021.
//
#include<stdio.h>

int main()
{
    char c = 205;

    printf("Signed -> %x %x\n", c, c & 0x00ff);

    unsigned char uc = 205;

    printf("Unsigned -> %x %x", uc, uc & 0x00ff);
}
