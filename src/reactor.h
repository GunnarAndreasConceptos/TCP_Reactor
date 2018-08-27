#ifndef REACTOR_H
#define REACTOR_H

#include "event_handler.h"

void Register(EventHandler *handler);
void Unregister(EventHandler *handler);

#endif