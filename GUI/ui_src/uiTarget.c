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
#include "headers/EqualizerViewer.h"

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
    gtk_widget_queue_draw(GTK_WIDGET(uiData->soundViewer));

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
        denoiseSignal(uiData);
    }
    wavRecoder(uiData->soundData, "res.wav");
    char* temp = "res.wav";
    char* newpath = malloc(sizeof (char) * 8);
    memcpy(newpath, temp, sizeof (char) * 8);
    uiData->soundPathNew = newpath;
    gtk_widget_queue_draw(GTK_WIDGET(uiData->soundViewer));
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
        gtk_widget_queue_draw(GTK_WIDGET(data->equalizerViewer));
    }
    else {
        gtk_widget_set_visible(GTK_WIDGET(data->windowEqualizer), gtk_false());
        data->equalizerMode = 0;
    }
}


void wavelet_target(WavData* data)
{
    //wavelet(data);
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
    gtk_widget_queue_draw(GTK_WIDGET(data->equalizerViewer));
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

    stopPlay(data);
    playSoundOld(data);
}

void onPlayNew(GtkButton* button, gpointer user_data)
{
    UIData* data = (UIData*)user_data;

    stopPlay(data);
    playSoundNew(data);
}


void onStop(GtkButton* button, gpointer user_data)
{
    UIData* data = (UIData*)user_data;
    stopPlay(data);
}

void onDrawSound(GtkWidget* widget, cairo_t* cr, gpointer user_data)
{
    UIData* data = (UIData*)user_data;
    GdkRectangle da;            /* GtkDrawingArea size */
    gdouble dx = 0.1, dy = 1.0; /* Pixels between each point */
    gdouble i, clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
    GdkWindow *window = gtk_widget_get_window(widget);

    /* Determine GtkDrawingArea dimensions */
    gdk_window_get_geometry (window,
                             &da.x,
                             &da.y,
                             &da.width,
                             &da.height);

    /* Draw on a black background */
    cairo_set_source_rgb (cr, 0.9, 0.9, 0.9);
    cairo_paint (cr);
    /* Change the transformation matrix */
    cairo_translate (cr, 0, da.height / 2);
    //cairo_scale (cr, 100, -100);

    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    cairo_set_line_width (cr, 2);

    /* Draws x and y axis */
    cairo_set_source_rgb (cr, 0.3, 0.3, 0.3);
    cairo_move_to (cr, clip_x1, 0.0);
    cairo_line_to (cr, clip_x2, 0.0);
    cairo_stroke (cr);
    cairo_set_line_width (cr, 0.3);
    cairo_move_to (cr, clip_x1, clip_y2 / 2);
    cairo_line_to (cr, clip_x2, clip_y2 / 2);
    cairo_move_to (cr, clip_x1, clip_y1 / 2);
    cairo_line_to (cr, clip_x2, clip_y1 / 2);
    cairo_stroke(cr);
    /* Link each data point */
    if (data->soundData == NULL)
        return;

    cairo_set_line_width(cr, 1);
    for (i = clip_x1; i < clip_x2; i += dx)
    {
        if ((i * data->soundData->addInfo->num_of_sample / clip_x2) >= data->soundData->addInfo->num_of_sample)
            break;
        double point = (double)(data->soundData->data[(int)(i * data->soundData->addInfo->num_of_sample / clip_x2)]) / data->soundData->addInfo->high_limit;
        point *= clip_y2;
        cairo_line_to (cr, i, point);
    }
    /* Draw the curve */
    cairo_set_source_rgba (cr, 0.3, 0.3, 1, 0.8);
    cairo_stroke (cr);
}

void onDrawEqualizer(GtkWidget* widget, cairo_t* cr, gpointer user_data)
{
    applyEquaPreview(widget, cr, (UIData*) user_data);
}
