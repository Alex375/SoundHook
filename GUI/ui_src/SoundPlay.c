//
// Created by Alexandre Josien on 14/06/2021.
//

#include "headers/SoundPlay.h"
#include "../type/types.h"
#include <err.h>




void stopPlay(UIData* data)
{
    if (data->playPidOld != NULL)
    {
        kill(*(data->playPidOld), SIGTERM);
    }
    free(data->playPidOld);
    data->playPidOld = NULL;
    if (data->playPidNew != NULL)
    {
        kill(*(data->playPidNew), SIGTERM);
    }
    free(data->playPidNew);
    data->playPidNew = NULL;
}



void playSoundOld(UIData* data)
{
    char* command = "afplay";
    char* argv[3];
    argv[0] = command;
    argv[1] = data->soundPathOld;
    argv[2] = NULL;
    pid_t pid = fork();
    if (pid < 0)
    {
        g_print("Error forking for play");
        return;
    }
    if (pid == 0)
    {
        execvp(command, argv);
        exit(0);
    }

    data->playPidOld = malloc(sizeof (pid_t));
    memcpy(data->playPidOld, &pid, sizeof (pid_t));
}


void playSoundNew(UIData* data)
{
    char* command = "afplay";
    char* argv[3];
    argv[0] = command;
    argv[1] = data->soundPathNew;
    argv[2] = NULL;
    pid_t pid = fork();
    if (pid < 0)
    {
        g_print("Error forking for play");
        return;
    }
    if (pid == 0)
    {
        execvp(command, argv);
        exit(0);
    }

    data->playPidNew = malloc(sizeof (pid_t));
    memcpy(data->playPidNew, &pid, sizeof (pid_t));
}

