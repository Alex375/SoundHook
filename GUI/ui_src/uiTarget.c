//
// Created by Alexandre Josien on 22/04/2021.
//

#include "headers/uiTarget.h"
#include <gtk/gtk.h>
#include <err.h>
#include "../type/types.h"
#include "../../file_decoder/wav/Decoder/headers/WavDecoder.h"
#include "../../file_decoder/wav/Recoder/headers/WavRecoder.h"
#include "../../file_decoder/wav/types/wav.h"
#include "../../file_decoder/wav/tools/headers/WavTools.h"
#include "../../decomposition/fft.h"
#include "../ui_tools/headers/UITools.h"

void fft_target(WavData* data);
void wavelet_target(WavData* data);

void on_file_set(GtkFileChooserButton *widget, gpointer data)
{
    while (g_main_context_iteration(NULL, FALSE));
    UIData* uiData = (UIData*)data;

    //TODO : Free old file path
    //if (uiData->soundPath != NULL)

    //free(uiData->soundPath);
    uiData->soundPath = gtk_file_chooser_get_filename((GtkFileChooser *) widget);
//    if (uiData->soundPath == NULL)
//        err(1,"Memory allocation failed");
//    g_print("File path -> %s\n", uiData->soundPath);


}

void on_go_pressed(GtkButton* widget, gpointer data)
{
    UIData* uiData = (UIData*)data;
    g_print("filepath -> %s\n", uiData->soundPath);
    //TODO : Fork to procedures

    //startProgressBar(uiData);
    WavData* wavData = decodeWave(uiData->soundPath);
    printWavHeader(wavData->header);

    wavRecoder(wavData, "/Users/alexandrejosien/Desktop/res.wav");

    if (uiData->fft_active == 1)
    {
        fft_target(wavData);
    }

    if (uiData->wavlet_active == 1)
    {
        wavelet_target(wavData);
    }

    freeWavData(wavData);
}

void on_check1(GtkToggleButton *togglebutton, gpointer user_data)
{
    UIData* uiData = (UIData*)user_data;
    if (gtk_toggle_button_get_active(togglebutton)) {
        uiData->fft_active = 1;
    }
    else {
        uiData->fft_active = 0;
    }
}

void on_check2(GtkToggleButton *togglebutton, gpointer user_data)
{
    UIData* uiData = (UIData*)user_data;
    if (gtk_toggle_button_get_active(togglebutton)) {
        uiData->wavlet_active = 1;
    }
    else {
        uiData->wavlet_active = 0;
    }
}

void fft_target(WavData* data)
{
    //    fft(wavData->data, wavData->addInfo->num_of_sample, wavData->addInfo->time, uiData->soundPath);
    g_print("fft\n");
}

void wavelet_target(WavData* data)
{
    g_print("Wavelet\n");
}