//
// Created by Alexandre Josien on 23/04/2021.
//

#include "headers/uiInit.h"
#include <err.h>
#include "headers/uiTarget.h"
#include "headers/SliderTagert.h"


UIData* init_data(GtkBuilder* builder)
{
    UIData* data = malloc(sizeof (UIData));
    if (data == NULL)
        err(EXIT_FAILURE, "Memory allocation failed");
    data->windowMain = GTK_WINDOW(gtk_builder_get_object(builder, "new_window"));
    data->fileChooserBtn = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "filechooser"));
    data->fourrier_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_fft"));
    data->wavlet_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_wavelet"));
    data->equalizer_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "check_equalizer"));
    data->playButtonOld = GTK_BUTTON(gtk_builder_get_object(builder, "btn_play_old"));
    data->playButtonNew = GTK_BUTTON(gtk_builder_get_object(builder, "btn_play_new"));
    data->applyBtn = GTK_BUTTON(gtk_builder_get_object(builder, "btn_apply"));
    data->saveBtn = GTK_BUTTON(gtk_builder_get_object(builder, "btn_save"));
    data->soundViewer = GTK_IMAGE(gtk_builder_get_object(builder, "sound_viewer"));
    data->fft_active = 0;
    data->wavlet_active = 0;
    data->soundData = NULL;

    data->windowEqualizer = GTK_WINDOW(gtk_builder_get_object(builder, "window_equalizer"));
    data->scale1 = GTK_SCALE(gtk_builder_get_object(builder, "scale1"));
    data->scale2 = GTK_SCALE(gtk_builder_get_object(builder, "scale2"));
    data->scale3 = GTK_SCALE(gtk_builder_get_object(builder, "scale3"));
    data->scale4 = GTK_SCALE(gtk_builder_get_object(builder, "scale4"));
    data->scale5 = GTK_SCALE(gtk_builder_get_object(builder, "scale5"));
    data->adjustment1 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment1"));
    data->adjustment2 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment2"));
    data->adjustment3 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment3"));
    data->adjustment4 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment4"));
    data->adjustment5 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment5"));
    data->equalizerValue = malloc(sizeof (double) * 5);
    if (data->equalizerValue ==  NULL)
        err(EXIT_FAILURE, "Memory allocation failed");
    for (size_t i = 0; i < 5; i++)
        data->equalizerValue[i] = 100;
    data->equalizerMode = 1;
    data->comboEqualizerMode = GTK_COMBO_BOX(gtk_builder_get_object(builder, "equlizermode"));


    data->windowProgressBar = GTK_WINDOW(gtk_builder_get_object(builder, "progress_bar_window"));
    data->progress_stop_btn = GTK_BUTTON(gtk_builder_get_object(builder, "stop_btn"));
    data->progress_bar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progress_bar"));
    data->progress_lbl = GTK_LABEL(gtk_builder_get_object(builder, "state_label"));


    data->file_filter = gtk_file_filter_new();
    gtk_file_filter_set_name(data->file_filter, "Sounds");
    gtk_file_filter_add_pattern(data->file_filter, "*.wav");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(data->fileChooserBtn), data->file_filter);
    data->soundPathOld = NULL;
    data->soundPathNew = NULL;
    data->playPidOld = NULL;
    data->playPidNew = NULL;

    return data;
}

void setSignal(UIData* data)
{
    g_signal_connect(data->windowMain, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(data->windowProgressBar, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(data->fileChooserBtn, "file-set", G_CALLBACK(on_file_set), data);
    g_signal_connect(data->playButtonOld, "pressed", G_CALLBACK(onPlayOld), data);
    g_signal_connect(data->playButtonNew, "pressed", G_CALLBACK(onPlayNew), data);
    g_signal_connect(data->applyBtn, "pressed", G_CALLBACK(on_go_pressed), data);
    g_signal_connect(data->saveBtn, "pressed", G_CALLBACK(on_save), data);
    g_signal_connect(data->fourrier_check, "toggled", G_CALLBACK(on_check1), data);
    g_signal_connect(data->wavlet_check, "toggled", G_CALLBACK(on_check2), data);
    g_signal_connect(data->equalizer_check, "toggled", G_CALLBACK(on_check3), data);

    g_signal_connect(data->adjustment1, "value-changed", G_CALLBACK(onAdjMoved1), data);
    g_signal_connect(data->adjustment2, "value-changed", G_CALLBACK(onAdjMoved2), data);
    g_signal_connect(data->adjustment3, "value-changed", G_CALLBACK(onAdjMoved3), data);
    g_signal_connect(data->adjustment4, "value-changed", G_CALLBACK(onAdjMoved4), data);
    g_signal_connect(data->adjustment5, "value-changed", G_CALLBACK(onAdjMoved5), data);
    g_signal_connect(data->comboEqualizerMode, "changed", G_CALLBACK(onEqualizerModeChanged), data);
}
