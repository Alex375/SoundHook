//
// Created by Alexandre Josien on 23/04/2021.
//

#ifndef SOUNDHOOK_TYPES_H
#define SOUNDHOOK_TYPES_H

#include <gtk/gtk.h>

typedef struct uiData uiData;
struct uiData {
    GtkWindow *windowMain;
    GtkFileChooserButton *fileChooserBtn;
    GtkCheckButton **analysButtonCollection;
    GtkButton *goButton;
};


#endif //SOUNDHOOK_TYPES_H
