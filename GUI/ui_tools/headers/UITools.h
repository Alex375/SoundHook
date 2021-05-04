//
// Created by Alexandre Josien on 24/04/2021.
//

#ifndef SOUNDHOOK_UITOOLS_H
#define SOUNDHOOK_UITOOLS_H

#include <gtk/gtk.h>
#include "../../type/types.h"

void create_message_box(GtkWindow* window, const char* message);
void startProgressBar(UIData* data);

#endif //SOUNDHOOK_UITOOLS_H
