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
    GtkWindow *windowEqualizer;
    GtkFileChooserButton *fileChooserBtn;
    GtkCheckButton* fourrier_check;
    GtkCheckButton* wavlet_check;
    GtkButton* equalizerBtn;
    GtkButton* applyBtn;
    GtkButton* saveBtn;
    GtkButton* progress_stop_btn;
    GtkProgressBar* progress_bar;
    GtkLabel* progress_lbl;
    GtkFileFilter* file_filter;
    int fft_active;
    int wavlet_active;
    WavData * soundData;
    GtkImage * soundViewer;

    GtkScale* scale1;
    GtkScale* scale2;
    GtkScale* scale3;
    GtkScale* scale4;
    GtkScale* scale5;
    GtkAdjustment* adjustment1;
    GtkAdjustment* adjustment2;
    GtkAdjustment* adjustment3;
    GtkAdjustment* adjustment4;
    GtkAdjustment* adjustment5;
    GtkComboBox* comboEqualizerMode;
    int equalizerMode;

    double* equalizerValue;


};


#endif //SOUNDHOOK_TYPES_H
