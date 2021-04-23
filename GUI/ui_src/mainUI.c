//
// Created by Alexandre Josien on 22/04/2021.
//

#include "headers/mainUI.h"
#include <gtk/gtk.h>
#include "headers/uiTarget.h"
#include "../type/types.h"
#include <err.h>
#include "headers/uiInit.h"


int main(int argc, char** argv)
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "../GUI/ui_glade/window_main.glade", NULL);

    UIData* uiData = init_data(builder);

    gtk_builder_connect_signals(builder, NULL);


    setSignal(uiData);

    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(GTK_WIDGET(uiData->windowMain));
    gtk_main();

    g_object_unref(builder);

    /////////FREE
    free(uiData);

    return 0;
}



