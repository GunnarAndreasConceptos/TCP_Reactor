#include "handle.h"












typedef Handle (*getHandleFunc)(void* instance);

typedef void (*handleEventFunc)(void* instance);



typedef struct

{

    void *instance;

    getHandleFunc get_handle;

    handleEventFunc handle_event;

} EventHandler;
