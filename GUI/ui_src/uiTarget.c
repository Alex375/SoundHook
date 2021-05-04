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

void fft_target(WavData* data);
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
        //printf("%f\n", in[i]);
    }
    grapherSize(xIn, in, 700, 350, dataSize, dataSize, ".start.png");
    /*GError *error = NULL;
    GdkPixbuf * pixBuf = gdk_pixbuf_new_from_file(".start.png", &error);
    if (pixBuf == NULL) {
        g_printerr ("Error loading file: #%d %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);
    }*/
    free(xIn);
    free(in);
    //gtk_image_set_from_pixbuf(GTK_IMAGE(uiData->soundViewer), GDK_PIXBUF(pixBuf));
    gtk_image_set_from_file(GTK_IMAGE(uiData->soundViewer), ".start.png");
}

void on_go_pressed(GtkButton* widget, gpointer data)
{
    UIData* uiData = (UIData*)data;
    //TODO : Fork to procedures



    if (uiData->fft_active == 1)
    {
        fft_target(uiData->soundData);
    }

    if (uiData->wavlet_active == 1)
    {
        wavelet_target(uiData->soundData);
    }
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
