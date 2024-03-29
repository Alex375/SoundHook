//
// Created by Alexandre Josien on 23/04/2021.
//

#ifndef SOUNDHOOK_TYPES_H
#define SOUNDHOOK_TYPES_H

#include <gtk/gtk.h>
#include <pthread.h>
#include "../../file_decoder/wav/types/wav.h"

typedef struct UIData UIData;
struct UIData {
    char* arg1;
    pid_t* playPidOld;
    pid_t* playPidNew;
    char* soundPathOld;
    char* soundPathNew;
    GtkWindow *windowMain;
    GtkWindow *windowProgressBar;
    GtkWindow *windowEqualizer;
    GtkFileChooserButton *fileChooserBtn;
    GtkCheckButton* fourrier_check;
    GtkCheckButton* wavlet_check;
    GtkCheckButton* equalizer_check;
    GtkButton* equalizerBtn;
    GtkButton* applyBtn;
    GtkButton* saveBtn;
    GtkButton* progress_stop_btn;
    GtkButton* reset_equa_btn;
    GtkProgressBar* progress_bar;
    GtkLabel* progress_lbl;
    GtkFileFilter* file_filter;
    int fft_active;
    int wavlet_active;
    WavData * soundData;
    GtkDrawingArea* soundViewer;
    GtkDrawingArea* equalizerViewer;

    GtkScale* scale1;
    GtkScale* scale2;
    GtkScale* scale3;
    GtkScale* scale4;
    GtkScale* scale5;
    GtkScale* scale6;
    GtkAdjustment* adjustment1;
    GtkAdjustment* adjustment2;
    GtkAdjustment* adjustment3;
    GtkAdjustment* adjustment4;
    GtkAdjustment* adjustment5;
    GtkAdjustment* adjustment6;

    GtkLabel* qFactLbl;

    GtkComboBox* comboEqualizerMode;
    int equalizerMode;

    GtkButton* playButtonOld;
    GtkButton* playButtonNew;
    GtkButton* btnStop;

    double* equalizerValue;
    double qFactor;


};

void freeUiData(UIData* data);


#endif //SOUNDHOOK_TYPES_H
