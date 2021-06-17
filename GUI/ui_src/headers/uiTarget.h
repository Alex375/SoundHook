//
// Created by Alexandre Josien on 22/04/2021.
//

#ifndef SOUNDHOOK_UITARGET_H
#define SOUNDHOOK_UITARGET_H

#include <gtk/gtk.h>

void on_file_set(GtkFileChooserButton *widget, gpointer filepath);
void on_go_pressed(GtkButton* widget, gpointer data);
void on_check1(GtkToggleButton *togglebutton, gpointer user_data);
void on_check2(GtkToggleButton *togglebutton, gpointer user_data);
void on_check3(GtkToggleButton *togglebutton, gpointer user_data);
void on_save(GtkFileChooserButton *widget, gpointer user_data);
void onEqualizerModeChanged(GtkComboBox *widget, gpointer user_data);
void onPlayOld(GtkButton* button, gpointer user_data);
void onPlayNew(GtkButton* button, gpointer user_data);
void onStop(GtkButton* button, gpointer user_data);


#endif //SOUNDHOOK_UITARGET_H
