//
// Created by Alexandre Josien on 31/03/2021.
//

#include "Graph.h"
#include "pbPlots.h"
#include "supportLib.h"

int grapher(double* xs, double* ys, size_t xlen, size_t ylen)
{


    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    DrawScatterPlot(canvasReference, 600, 400, xs, xlen, ys, ylen);

    size_t length;
    double *pngdata = ConvertToPNG(&length, canvasReference->image);
    WriteToFile(pngdata, length, "example1.png");
    DeleteImage(canvasReference->image);

    return 0;
}