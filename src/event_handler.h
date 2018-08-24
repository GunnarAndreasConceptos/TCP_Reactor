#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "handle.h"

/* All interaction from Reactor to an event handler goes 
through function pointers with the following signatures: */
typedef Handle (*getHandleFunc)(void* instance);
typedef void (*handleEventFunc)(void* instance);

typedef struct
{
    void *instance;
    getHandleFunc get_handle;
    handleEventFunc handle_event;
} EventHandler;

#endif //EVENT_HANDLER_H