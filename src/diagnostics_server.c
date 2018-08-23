#include "diagnostics_server.h"

#include <stdlib.h>

struct DiagnosticsServer
{
    //TODO: Add rest of the struct
    int Handle;
};

DiagnosticsServerPtr createServer(unsigned int tcpPort)
{
    DiagnosticsServerPtr newServer = malloc(sizeof *newServer);

    return newServer;
}