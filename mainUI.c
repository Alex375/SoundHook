//
// Created by Alexandre Josien on 22/04/2021.
//

#include "GUI/ui_src/headers/mainUI.h"
#include <gtk/gtk.h>
#include "GUI/ui_src/headers/uiTarget.h"
#include "GUI/type/types.h"
#include <err.h>
#include "GUI/ui_src/headers/uiInit.h"
#include "GUI/ui_src/headers/uiTarget.h"
#include "GUI/ui_src/headers/SoundPlay.h"


int main(int argc, char** argv)
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "GUI/ui_glade/window_main.glade", NULL);

    UIData* uiData = init_data(builder);

    gtk_builder_connect_signals(builder, NULL);


    setSignal(uiData);

    uiData->arg1 = argv[0];
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show(GTK_WIDGET(uiData->windowMain));
    gtk_main();


    /////////FREE

    stopPlay(uiData);
    freeUiData(uiData);


    return 0;
}

