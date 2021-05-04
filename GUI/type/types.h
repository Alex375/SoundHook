//
// Created by Alexandre Josien on 23/04/2021.
//

#ifndef SOUNDHOOK_TYPES_H
#define SOUNDHOOK_TYPES_H

#include <gtk/gtk.h>
#include "../../file_decoder/wav/types/wav.h"

typedef struct UIData UIData;
struct UIData {
    GtkWindow *windowMain;
    GtkWindow *windowProgressBar;
    GtkFileChooserButton *fileChooserBtn;
    GtkCheckButton* fourrier_check;
    GtkCheckButton* wavlet_check;
    GtkButton *goButton;
    GtkButton* progress_stop_btn;
    GtkProgressBar* progress_bar;
    GtkLabel* progress_lbl;
    GtkFileFilter* file_filter;
    int fft_active;
    int wavlet_active;
    char* soundPath;
    WavData * resultData;
};


#endif //SOUNDHOOK_TYPES_H
