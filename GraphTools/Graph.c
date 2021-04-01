//
// Created by Alexandre Josien on 31/03/2021.
//

#include "Graph.h"
#include "pbPlots.h"
#include "supportLib.h"

void grapher(double* xs, double* ys, size_t xlen, size_t ylen, char* name)
{


    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference, 1920, 1080, xs, xlen, ys, ylen);

    size_t length;
    double *pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, name);
    DeleteImage(canvasReference->image);


}