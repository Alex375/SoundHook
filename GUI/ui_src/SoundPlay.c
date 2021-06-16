//
// Created by Alexandre Josien on 14/06/2021.
//

#include "headers/SoundPlay.h"
#include "../type/types.h"
#include <err.h>


void playerCheck(UIData* data)
{
    if (data->playPidOld != NULL)
        kill(*data->playPidOld, SIGTERM);
    if (data->playPidNew != NULL)
        kill(*data->playPidNew, SIGTERM);
    if (data->playThreadNew != NULL)
        pthread_join(*data->playThreadNew, NULL);
    if (data->playThreadOld != NULL)
        pthread_join(*data->playThreadOld, NULL);
    if (data->playPidNew != NULL)
    {
        free(data->playPidNew);
        data->playPidNew = NULL;
    }
    if (data->playPidOld != NULL)
    {
        free(data->playPidOld);
        data->playPidOld = NULL;
    }
    if (data->playThreadNew != NULL)
    {
        free(data->playThreadNew);
        data->playThreadNew = NULL;
    }
    if (data->playThreadOld != NULL)
    {
        free(data->playThreadOld);
        data->playThreadOld = NULL;
    }
}


void soundWorker(UIData* data, int old)
{
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
}



void stopSoundOld(UIData* data)
{
    if (data->playPidOld == NULL || data->playThreadOld == NULL)
        return;
    if(kill(*data->playPidOld, SIGTERM) == -1)
    {
        g_print("Error killing old sound subprocess\n");
    }
    free(data->playPidOld);
    data->playPidOld = NULL;
}

void stopSoundNew(UIData* data)
{
    g_print("Canceling new\n");
    if (data->playPidNew == NULL || data->playThreadNew == NULL)
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

    soundWorker(data, 1);
    gtk_button_set_label(GTK_BUTTON(data->playButtonOld), "Play");

    pid_t* tempp = data->playPidOld;
    data->playPidOld = NULL;
    free(tempp);
    pthread_t* tempt = data->playThreadOld;
    data->playThreadOld = NULL;
    free(tempt);
    pthread_exit(NULL);
}


void* playSoundNew(void* arg)
{
    UIData* data = (UIData*)arg;


    if (data->soundPathNew == NULL)
        pthread_exit(NULL);


    gtk_button_set_label(GTK_BUTTON(data->playButtonNew), "Stop");

    soundWorker(data, 0);
    gtk_button_set_label(GTK_BUTTON(data->playButtonNew), "Play");

    pid_t* tempp = data->playPidNew;
    data->playPidNew = NULL;
    free(tempp);
    pthread_t* tempt = data->playThreadNew;
    data->playThreadNew = NULL;
    free(tempt);
    pthread_exit(NULL);
}

