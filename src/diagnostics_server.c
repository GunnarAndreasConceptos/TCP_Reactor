#include "diagnostics_server.h"

#include <stdlib.h>

struct DiagnosticsServer
{
    //TODO: Add rest of the struct
    int Port;
};

DiagnosticsServerPtr createServer(unsigned int tcpPort)
{
    DiagnosticsServerPtr newServer = malloc(sizeof *newServer);
    
    if (newServer == NULL)
    {
        return newServer;
    }

    newServer->Port = tcpPort;
}

void destroyServer(DiagnosticsServerPtr* server)
{
    if (server != NULL)
    {
        free(*server);
        //We do this so that destroyServer is testable
        *server = NULL;
    }
}