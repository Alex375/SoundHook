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
#include "../../wavlet/headers/Wavelet.h"

void fft_target(WavData* data);
void wavelet_target(WavData* data);
void on_save(UIData * data);


void on_file_set(GtkFileChooserButton *widget, gpointer data)
{
    while (g_main_context_iteration(NULL, FALSE));
    UIData* uiData = (UIData*)data;
    //TODO : Free old file path

    uiData->soundPath = gtk_file_chooser_get_filename((GtkFileChooser *) widget);


}

void on_go_pressed(GtkButton* widget, gpointer data)
{
    UIData* uiData = (UIData*)data;
    g_print("filepath -> %s\n", uiData->soundPath);
    //TODO : Fork to procedures

    //startProgressBar(uiData);
    WavData* wavData = decodeWave(uiData->soundPath);
    printWavHeader(wavData->header);

    if (uiData->fft_active == 1)
    {
        fft_target(wavData);
    }

    if (uiData->wavlet_active == 1)
    {
        wavelet_target(wavData);
    }
    uiData->resultData = wavData;
    on_save(uiData);
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
    wavelet(data);
}

void on_save(UIData * data)
{
    GtkWidget* save_file_dialog = gtk_file_chooser_dialog_new ("Save File",
                                                               data->windowMain,
                                                               GTK_FILE_CHOOSER_ACTION_SAVE,
                                                               ("_Cancel"),
                                                               GTK_RESPONSE_CANCEL,
                                                               ("_Save"),
                                                               GTK_RESPONSE_ACCEPT,
                                                               NULL);
    GtkFileChooser* save_file_choose = GTK_FILE_CHOOSER(save_file_dialog);
    gint res = gtk_dialog_run (GTK_DIALOG (save_file_dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *path;
        path = gtk_file_chooser_get_filename(save_file_choose);
        wavRecoder(data->resultData, path);
        g_free(path);
    }

    gtk_widget_destroy (save_file_dialog);
}