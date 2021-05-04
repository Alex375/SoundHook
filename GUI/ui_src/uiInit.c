//
// Created by Alexandre Josien on 23/04/2021.
//

#include "headers/uiInit.h"
#include <err.h>
#include "headers/uiTarget.h"


UIData* init_data(GtkBuilder* builder)
{
    UIData* data = malloc(sizeof (UIData));
    if (data == NULL)
        err(EXIT_FAILURE, "Memory allocation failed");
    data->windowMain = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    data->windowProgressBar = GTK_WINDOW(gtk_builder_get_object(builder, "progress_bar_window"));
    data->fileChooserBtn = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file_chooser_btn"));
    data->fourrier_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "fft_check"));
    data->wavlet_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "wavelet_check"));
    data->goButton = GTK_BUTTON(gtk_builder_get_object(builder, "go_btn"));
    data->progress_stop_btn = GTK_BUTTON(gtk_builder_get_object(builder, "stop_btn"));
    data->progress_bar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progress_bar"));
    data->progress_lbl = GTK_LABEL(gtk_builder_get_object(builder, "state_label"));
    data->soundPath = calloc(1, sizeof (char));
    data->fft_active = 0;
    data->wavlet_active = 0;
    data->resultData = NULL;

    data->file_filter = gtk_file_filter_new();
    gtk_file_filter_set_name(data->file_filter, "Sounds");
    gtk_file_filter_add_pattern(data->file_filter, "*.wav");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(data->fileChooserBtn), data->file_filter);

    return data;
}

void setSignal(UIData* data)
{
    g_signal_connect(data->windowMain, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(data->windowProgressBar, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(data->fileChooserBtn, "file-set", G_CALLBACK(on_file_set), &data);
    g_signal_connect(data->goButton, "pressed", G_CALLBACK(on_go_pressed), &data);
    g_signal_connect(data->fourrier_check, "toggled", G_CALLBACK(on_check1), &data);
    g_signal_connect(data->wavlet_check, "toggled", G_CALLBACK(on_check2), &data);
}
