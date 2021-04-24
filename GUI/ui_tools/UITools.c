//
// Created by Alexandre Josien on 24/04/2021.
//

#include "headers/UITools.h"
#include <gtk/gtk.h>
#include "../type/types.h"


void create_message_box(GtkWindow* window, const char* message)
{
    GtkWidget* dialog = gtk_message_dialog_new(window,GTK_RESPONSE_NONE,GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,"%s", message);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

void startProgressBar(UIData* data)
{
    while (g_main_context_iteration(NULL, FALSE));
    gtk_widget_show(GTK_WIDGET(data->windowProgressBar));
}