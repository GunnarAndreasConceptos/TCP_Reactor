#include "diagnostics_server.h"
#include "handle.h"

#include <stdlib.h>

struct DiagnosticsServer
{
    Handle listeningSocket;
    //TODO: Add rest of the struct
};

DiagnosticsServerPtr createServer(unsigned int tcpPort)
{
    DiagnosticsServerPtr newServer = malloc(sizeof *newServer);
    
    if (newServer == NULL)
    {
        return newServer;
    }
}

void destroyServer(DiagnosticsServerPtr server)
{
    free(server);
}