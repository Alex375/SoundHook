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
#include <pthread.h>
#include "headers/SoundPlay.h"

void wavelet_target(WavData* data);




void on_file_set(GtkFileChooserButton *widget, gpointer data)
{

    UIData* uiData = (UIData*)data;
    uiData->soundPathNew = NULL;
    if (uiData->soundPathOld != NULL)
        free(uiData->soundPathOld);
    uiData->soundPathOld = gtk_file_chooser_get_filename((GtkFileChooser *) widget);
    if (uiData->soundData != NULL)
        freeWavData(uiData->soundData);
    uiData->soundData = decodeWave(uiData->soundPathOld);
    printWavHeader(uiData->soundData->header);

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
}

void on_go_pressed(GtkButton* widget, gpointer data)
{
    UIData* uiData = (UIData*)data;
    //TODO : Fork to procedures

    //gtk_widget_show(GTK_WIDGET(uiData->windowProgressBar));

    short eqactive = 0;
    for (size_t i = 0; i < 5; i++)
    {
        if (uiData->equalizerValue[i] != 100)
            eqactive = 1;
    }
    if (!eqactive)
        uiData->equalizerMode = 0;

    if(uiData->fft_active || uiData->equalizerMode)
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
    wavRecoder(uiData->soundData, "res.wav");
    char* temp = "res.wav";
    char* newpath = malloc(sizeof (char) * 8);
    memcpy(newpath, temp, sizeof (char) * 8);
    uiData->soundPathNew = newpath;
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

void on_check3(GtkToggleButton *togglebutton, gpointer user_data)
{
    UIData* data = (UIData*)user_data;
    gtk_widget_show(GTK_WIDGET(data->windowEqualizer));
    if (gtk_toggle_button_get_active(togglebutton)) {
        gtk_widget_set_visible(GTK_WIDGET(data->windowEqualizer), gtk_true());
        data->equalizerMode = 1;
    }
    else {
        gtk_widget_set_visible(GTK_WIDGET(data->windowEqualizer), gtk_false());
        data->equalizerMode = 0;
    }
}


void wavelet_target(WavData* data)
{
    //wavelet(data);
    g_print("Wavelet\n");
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
        printWavHeader(data->soundData->header);
        path = gtk_file_chooser_get_filename(save_file_choose);
        wavRecoder(data->soundData, path);
        g_free(path);
    }

    gtk_widget_destroy (save_file_dialog);
}


void onEqualizerModeChanged(GtkComboBox *widget, gpointer user_data)
{
    UIData* data = (UIData*)user_data;
    data->equalizerMode = gtk_combo_box_get_active(widget) + 1;
    if (data->equalizerMode == 1)
    {
        gtk_widget_set_visible(GTK_WIDGET(data->qFactLbl), gtk_false());
        gtk_widget_set_visible(GTK_WIDGET(data->scale6), gtk_false());
    }
    else
    {
        gtk_widget_set_visible(GTK_WIDGET(data->qFactLbl), gtk_true());
        gtk_widget_set_visible(GTK_WIDGET(data->scale6), gtk_true());
    }
}


void onPlayOld(GtkButton* button, gpointer user_data)
{
    UIData* data = (UIData*)user_data;
    if (data->playPidOld != NULL)
    {
        playerCheck(data);
        return;
    }
    playerCheck(data);
    if (data->soundPathOld != NULL)
    {
        data->playThreadOld = malloc(sizeof (pthread_t));
        pthread_create(data->playThreadOld, NULL, playSoundOld, user_data);
    }
}

void onPlayNew(GtkButton* button, gpointer user_data)
{
    UIData* data = (UIData*)user_data;


    if (data->playPidNew != NULL)
    {
        playerCheck(data);
        return;
    }
    playerCheck(data);
    if (data->soundPathNew != NULL)
    {
        data->playThreadNew = malloc(sizeof (pthread_t));
        pthread_create(data->playThreadNew, NULL, playSoundNew, user_data);
    }
}
