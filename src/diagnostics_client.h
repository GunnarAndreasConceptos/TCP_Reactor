#ifndef DIAGNOSTICS_CLIENT_H
#define DIAGNOSTICS_CLIENT_H

#include "handle.h"
#include "server_event_notifier.h"

//Incomplete type to hide struct internals
typedef struct DiagnosticsClient *DiagnosticsClientPtr;

DiagnosticsClientPtr createClient(Handle server_handle, const ServerEventNotifier *event_notifier);

void destroyClient(DiagnosticsClientPtr client);

#endif  //DIAGNOSTICS_CLIENT_H