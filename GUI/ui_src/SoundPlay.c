//
// Created by Alexandre Josien on 14/06/2021.
//

#include "headers/SoundPlay.h"
#include "../type/types.h"
#include <err.h>


void soundWorker(UIData* data, int old)
{
    g_print("Play started\n");
    char* command = "afplay";
    char* argv[3];
    argv[0] = command;
    if (old)
        argv[1] = data->soundPathOld;
    else
        argv[1] = data->soundPathNew;
    argv[2] = NULL;
    pid_t pid = fork();
    if (pid < 0)
    {
        g_print("Error forking for play\n");
        return;
    }
    if (pid == 0)
    {
        execvp(command, argv);
        exit(0);
    }
    int status;

    if (old)
    {
        data->playPidOld = malloc(sizeof (pid_t));
        memcpy(data->playPidOld, &pid, sizeof (pid_t));
    }
    else
    {
        data->playPidNew = malloc(sizeof (pid_t));
        memcpy(data->playPidNew, &pid, sizeof (pid_t));
    }
    waitpid(pid, &status, WCONTINUED);
    g_print("Play ended\n");
}



void stopSoundOld(UIData* data)
{
    if (data->playPidOld == NULL)
        return;
    g_print("Canceling\n");
    if(kill(*data->playPidOld, SIGTERM) == -1)
    {
        g_print("Error killing old sound subprocess\n");
    }
    free(data->playPidOld);
    data->playPidOld = NULL;
}

void stopSoundNew(UIData* data)
{
    if (data->playPidNew == NULL)
        return;
    if(kill(*data->playPidNew, SIGTERM) == -1)
    {
        g_print("Error killing new sound subprocess\n");
    }
    free(data->playPidNew);
    data->playPidNew = NULL;
}

void* playSoundOld(void* arg)
{
    UIData* data = (UIData*)arg;


    if (data->soundPathOld == NULL)
        pthread_exit(NULL);

    gtk_button_set_label(GTK_BUTTON(data->playButtonOld), "Stop");

    g_print("Old started\n");
    soundWorker(data, 1);
    g_print("Old ended\n");
    gtk_button_set_label(GTK_BUTTON(data->playButtonOld), "Play");
    if (data->playPidOld != NULL)
        free(data->playPidOld);
    data->playPidOld = NULL;
    pthread_exit(NULL);
}


void* playSoundNew(void* arg)
{
    UIData* data = (UIData*)arg;


    if (data->soundPathNew == NULL)
        pthread_exit(NULL);

    gtk_button_set_label(GTK_BUTTON(data->playButtonNew), "Stop");

    g_print("Old started\n");
    soundWorker(data, 0);
    g_print("Old ended\n");
    gtk_button_set_label(GTK_BUTTON(data->playButtonNew), "Play");
    if (data->playPidNew != NULL)
        free(data->playPidNew);
    data->playPidNew = NULL;
    pthread_exit(NULL);
}

