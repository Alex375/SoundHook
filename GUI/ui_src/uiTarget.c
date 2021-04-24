//
// Created by Alexandre Josien on 22/04/2021.
//

#include "headers/uiTarget.h"
#include <gtk/gtk.h>
#include <err.h>
#include "../type/types.h"
#include "../../file_decoder/wav/Decoder/headers/WavDecoder.h"
#include "../../file_decoder/wav/types/wav.h"
#include "../../file_decoder/wav/tools/headers/WavTools.h"
#include "../../decomposition/fft.h"
#include "../ui_tools/headers/UITools.h"



void on_file_set(GtkFileChooserButton *widget, gpointer data)
{
    while (g_main_context_iteration(NULL, FALSE));
    UIData* uiData = (UIData*)data;

    //TODO : Free old file path
    //if (uiData->soundPath != NULL)

    //free(uiData->soundPath);
    uiData->soundPath = gtk_file_chooser_get_filename((GtkFileChooser *) widget);
    if (uiData->soundPath == NULL)
        err(1,"Memory allocation failed");
    g_print("File path -> %s\n", uiData->soundPath);
}

void on_go_pressed(GtkButton* widget, gpointer data)
{
    UIData* uiData = (UIData*)data;
    g_print("filepath -> %s\n", uiData->soundPath);
    //TODO : Fork to procedures

    startProgressBar(uiData);
    WavData* wavData = decodeWave(uiData->soundPath);
    printWavHeader(wavData->header);

    fft(wavData->data, wavData->addInfo->num_of_sample, wavData->addInfo->time, uiData->soundPath);
}
