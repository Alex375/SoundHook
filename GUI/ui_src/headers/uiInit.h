//
// Created by Alexandre Josien on 23/04/2021.
//

#ifndef SOUNDHOOK_UIINIT_H
#define SOUNDHOOK_UIINIT_H

#include <gtk/gtk.h>
#include "../../type/types.h"

UIData* init_data(GtkBuilder* builder);
void setSignal(UIData* data);

#endif //SOUNDHOOK_UIINIT_H
