//
// Created by Alexandre Josien on 17/06/2021.
//

#include "headers/EqualizerViewer.h"
#include "../../decomposition/Treat/previewEqua.h"
#include <gtk/gtk.h>
#include "../type/types.h"

#define EQUALEN 4000

void applyEquaPreview(GtkWidget* widget, cairo_t* cr, UIData* data)
{
    double* values = previewEqua(data->equalizerValue, data->qFactor, data->equalizerMode);
    GdkRectangle da;            /* GtkDrawingArea size */
    gdouble dx = 1, dy = 1.0; /* Pixels between each point */
    gdouble i, clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
    GdkWindow *window = gtk_widget_get_window(widget);

    /* Determine GtkDrawingArea dimensions */
    gdk_window_get_geometry (window,
                             &da.x,
                             &da.y,
                             &da.width,
                             &da.height);

    /* Draw on a black background */
    cairo_set_source_rgb (cr, 0.9, 0.9, 0.9);
    cairo_paint (cr);
    /* Change the transformation matrix */
    cairo_translate (cr, 0, da.height / 2);
    //cairo_scale (cr, 100, -100);

    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    cairo_set_line_width (cr, 2);


    /* Link each data point */
    if (values == NULL)
        return;

    cairo_set_line_width(cr, 1);
    for (i = clip_x1; i < clip_x2; i += dx)
    {
        if ((i * EQUALEN / clip_x2) >= EQUALEN)
            break;
        double point = (double)(values[(int)(i * EQUALEN / clip_x2)] - 100) / 201;
        point *= (clip_y2 - clip_y1);
        cairo_line_to (cr, i, -point);
    }
    /* Draw the curve */
    cairo_set_source_rgba (cr, 0.3, 0.3, 1, 0.8);
    cairo_stroke (cr);
    free(values);
}
