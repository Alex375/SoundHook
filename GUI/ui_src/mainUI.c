//
// Created by Alexandre Josien on 22/04/2021.
//

#include "headers/mainUI.h"
#include <gtk/gtk.h>
#include "headers/uiTarget.h"
#include "../type/types.h"
#include <err.h>

UIData* init_data(GtkBuilder* builder);

int main(int argc, char** argv)
{
    GtkBuilder      *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "../GUI/ui_glade/window_main.glade", NULL);

    UIData* uiData = init_data(builder);

    gtk_builder_connect_signals(builder, NULL);




    gtk_widget_show(GTK_WIDGET(uiData->windowMain));
    gtk_main();

    g_object_unref(builder);

    //FREE
    free(uiData);

    return 0;
}


UIData* init_data(GtkBuilder* builder)
{
    UIData* data = malloc(sizeof (UIData));
    if (data == NULL)
        err(EXIT_FAILURE, "Memory allocation failed");
    data->windowMain = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    data->fileChooserBtn = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "file_chooser_btn"));
    data->fourrier_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "fft_check"));
    data->wavlet_check = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "wavelet_check"));
    data->goButton = GTK_BUTTON(gtk_builder_get_object(builder, "go_btn"));
    data->progress_stop_btn = GTK_BUTTON(gtk_builder_get_object(builder, "stop_btn"));
    data->progress_bar = GTK_PROGRESS_BAR(gtk_builder_get_object(builder, "progress_bar"));
    data->progress_lbl = GTK_LABEL(gtk_builder_get_object(builder, "state_label"));


    data->file_filter = gtk_file_filter_new();
    gtk_file_filter_set_name(data->file_filter, "Sounds");
    gtk_file_filter_add_pattern(data->file_filter, "*.wav");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(data->fileChooserBtn), data->file_filter);

    return data;
}
