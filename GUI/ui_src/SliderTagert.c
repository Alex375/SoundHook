//
// Created by Alexandre Josien on 05/05/2021.
//

#include "headers/SliderTagert.h"
#include <gtk/gtk.h>
#include "../type/types.h"
#include "headers/EqualizerViewer.h"


void onAdjMoved1(GtkAdjustment* adjustment, gpointer user_data)
{
    UIData * data = (UIData*)user_data;
    data->equalizerValue[0] = gtk_adjustment_get_value(adjustment);
    applyEquaPreview(data);
}

void onAdjMoved2(GtkAdjustment* adjustment, gpointer user_data)
{
    UIData * data = (UIData*)user_data;
    data->equalizerValue[1] = gtk_adjustment_get_value(adjustment);
    applyEquaPreview(data);
}

void onAdjMoved3(GtkAdjustment* adjustment, gpointer user_data)
{
    UIData * data = (UIData*)user_data;
    data->equalizerValue[2] = gtk_adjustment_get_value(adjustment);
    applyEquaPreview(data);
}

void onAdjMoved4(GtkAdjustment* adjustment, gpointer user_data)
{
    UIData * data = (UIData*)user_data;
    data->equalizerValue[3] = gtk_adjustment_get_value(adjustment);
    applyEquaPreview(data);
}

void onAdjMoved5(GtkAdjustment* adjustment, gpointer user_data)
{
    UIData * data = (UIData*)user_data;
    data->equalizerValue[4] = gtk_adjustment_get_value(adjustment);
    applyEquaPreview(data);
}


void onAdjMoved6(GtkAdjustment* adjustment, gpointer user_data)
{
    UIData * data = (UIData*)user_data;
    data->qFactor = gtk_adjustment_get_value(adjustment);
    applyEquaPreview(data);
}
