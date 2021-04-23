//
// Created by Alexandre Josien on 22/04/2021.
//

#include "headers/uiTarget.h"
#include <gtk/gtk.h>
#include <err.h>


void on_image_choose(GtkFileChooserButton *widget, gpointer filepath)
{
    while (g_main_context_iteration(NULL, FALSE));

    filepath = gtk_file_chooser_get_filename((GtkFileChooser *) widget);
    if (filepath == NULL)
        err(1,"Not enough memory");


    //Progress_Set(data->ui.progress_main,0.1,data);

    //g_print("Image loaded\n");

    g_print("File path -> %s\n", filepath);
}

