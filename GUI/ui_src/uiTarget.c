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
#include "../../GraphTools/Graph.h"

void wavelet_target(WavData* data);




void on_file_set(GtkFileChooserButton *widget, gpointer data)
{
    UIData* uiData = (UIData*)data;
    //TODO : Free old file path

    char* soundPath = gtk_file_chooser_get_filename((GtkFileChooser *) widget);
    uiData->soundData = decodeWave(soundPath);
    g_free(soundPath);
    printWavHeader(uiData->soundData->header);
    //if (uiData->soundData != NULL)
      //  freeWavData(uiData->soundData);
    long dataSize = uiData->soundData->addInfo->num_of_sample;
    double * xIn = malloc(sizeof (double) * dataSize);
    for (size_t i = 0; i < dataSize; i++)
    {
        xIn[i] = (double)i;
    }
    double * in  = malloc(sizeof (double) * dataSize);
    if (in == NULL)
        err(EXIT_FAILURE, "Memory allocation failed");
    for (int i = 0; i < dataSize; ++i)
    {
        in[i] = ((double)uiData->soundData->data[i]) ;
    }
    grapherSize(xIn, in, 700, 350, dataSize, dataSize, ".start.png");

    free(xIn);
    free(in);
    gtk_image_set_from_file(GTK_IMAGE(uiData->soundViewer), ".start.png");
    for (size_t i = 0; i < 5; i++)
        uiData->equalizerValue[i] = 100;
    uiData->equalizerMode = 1;
}

void on_go_pressed(GtkButton* widget, gpointer data)
{
    UIData* uiData = (UIData*)data;
    //TODO : Fork to procedures

    gtk_widget_show(GTK_WIDGET(uiData->windowProgressBar));

    short eqactive = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (uiData->equalizerValue[i] != 100)
            eqactive = 1;
    }
    if (!eqactive)
        uiData->equalizerMode = 0;

    fftCall(uiData);


    if (uiData->wavlet_active == 1)
    {
        wavelet_target(uiData->soundData);
    }
    long dataSize = uiData->soundData->addInfo->num_of_sample;
    double * xIn = malloc(sizeof (double) * dataSize);
    for (size_t i = 0; i < dataSize; i++)
    {
        xIn[i] = (double)i;
    }
    double * in  = malloc(sizeof (double) * dataSize);
    if (in == NULL)
        err(EXIT_FAILURE, "Memory allocation failed");
    for (int i = 0; i < dataSize; ++i)
    {
        in[i] = ((double)uiData->soundData->data[i]) ;
    }
    grapherSize(xIn, in, 700, 350, dataSize, dataSize, ".res.png");

    free(xIn);
    free(in);
    gtk_image_set_from_file(GTK_IMAGE(uiData->soundViewer), ".res.png");
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


void wavelet_target(WavData* data)
{
    wavelet(data);
}

void on_save(GtkFileChooserButton *widget, gpointer user_data)
{
    UIData * data = user_data;
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
        wavRecoder(data->soundData, path);
        g_free(path);
    }

    gtk_widget_destroy (save_file_dialog);
}

void onLaunchEqualizer(GtkFileChooserButton *widget, gpointer user_data)
{
    UIData* data = (UIData*)user_data;
    gtk_widget_show(GTK_WIDGET(data->windowEqualizer));
}


void onEqualizerModeChanged(GtkComboBox *widget, gpointer user_data)
{
    UIData* data = (UIData*)user_data;
    data->equalizerMode = gtk_combo_box_get_active(widget) + 1;
}
