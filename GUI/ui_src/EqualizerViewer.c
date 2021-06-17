//
// Created by Alexandre Josien on 17/06/2021.
//

#include "headers/EqualizerViewer.h"
#include "../../decomposition/Treat/previewEqua.h"
#include <gtk/gtk.h>
#include "../type/types.h"

void applyEquaPreview(UIData* data)
{
    previewEqua(data->equalizerValue, data->qFactor, data->equalizerMode);
    gtk_image_set_from_file(GTK_IMAGE(data->equalizerViewer), "coefs.png");
}
