#include "diagnostics_server.h"
#include "event_handler.h"
#include "diagnostics_client.h"
#include "server_event_notifier.h"
#include "tcp_server.h"
#include "reactor.h"

#include <stdlib.h>
#include <stdio.h>

#define MAX_NO_OF_CLIENTS 19

struct DiagnosticsServer
{
    Handle listening_socket;
    EventHandler event_handler;

    /* All connected clients able to send diagnostics message. */
    DiagnosticsClientPtr clients[MAX_NO_OF_CLIENTS];
};

/* Function declarations */
static void deletaAllClients(DiagnosticsServerPtr server);
static int matchControlledClientByPointer(const DiagnosticsServerPtr server,
                                            const DiagnosticsClientPtr client_to_matc);
static int findFreeClientSlot(const DiagnosticsServerPtr server);
static int findMatchingClientSlot(const DiagnosticsServerPtr server,
                                    const DiagnosticsClientPtr client);
static Handle getServerSocket(void* instance);
static void handleConnectRequest(void* instance);
static void onClientClosed(void* server, void* closed_client);

/* EventHandler implementations */
static Handle getServerSocket(void* instance)
{
    const DiagnosticsServerPtr server = instance;
    return server->listening_socket;
}

static void handleConnectRequest(void* instance)
{
    DiagnosticsServerPtr server = instance;
    const int free_slot = findFreeClientSlot(server);

    if (0 <= free_slot)
    {
        //Create a callback for events requiring the actions of the server
        ServerEventNotifier event_notifier = {0};
        event_notifier.server = server;
        event_notifier.on_client_closed = onClientClosed;

        server->clients[free_slot] = createClient(server->listening_socket, &event_notifier);
        printf("Server: Incoming connect request accepted\n");
    }
    else
    {
        printf("Server: Not space for more clients");
    }
}

/**
* Implement server event notifiers
* This function is invoked as a callback from the client representation 
* in case it detects a disconnect on TCP level. 
*/
static void onClientClosed(void* server, void* closed_client)
{
    DiagnosticsServerPtr server_instance = server;
    DiagnosticsClientPtr client_instance = closed_client;

    const int client_slot = findMatchingClientSlot(server_instance, client_instance);
    if (0 > client_slot)
    {
        printf("Phantom client detected");
        return;
    }

    destroyClient(client_instance);
    server_instance->clients[client_slot] = NULL;
}

/* Implement server ADT functions */
DiagnosticsServerPtr createServer(unsigned int tcp_port)
{
    DiagnosticsServerPtr new_server = malloc(sizeof *new_server);
    
    if (new_server != NULL)
    {
        int i = 0;
        for (i = 0; i < MAX_NO_OF_CLIENTS; ++i)
        {
            new_server->clients[i] = NULL;
        }

        new_server->listening_socket = createServerSocket(tcp_port);

        new_server->event_handler.instance = new_server;
        new_server->event_handler.get_handle = getServerSocket;
        new_server->event_handler.handle_event = handleConnectRequest;

        Register(&new_server->event_handler);
    }

    return new_server;
}

void destroyServer(DiagnosticsServerPtr server)
{
    deletaAllClients(server);

    Unregister(&server->event_handler);

    disposeServerSocket(server->listening_socket);
    free(server);
}

/* Local functions */

static void deletaAllClients(DiagnosticsServerPtr server)
{
    int i = 0;
    for (i = 0; i < MAX_NO_OF_CLIENTS; ++i)
    {
        if (NULL != server->clients[i])
        {
            destroyClient(server->clients[i]);
        }
    }
}

/**
* Returns the index where a client matching the given pointer is found in client table
* Returns -1 if no match was found
*/
static int matchControlledClientByPointer(const DiagnosticsServerPtr server,
                                            const DiagnosticsClientPtr client_to_match)
{
    int client_slot = -1;
    int slot_found = 0;
    int i = 0;

    for (i = 0; (i < MAX_NO_OF_CLIENTS) && (0 == slot_found); ++i)
    {
        if (client_to_match == server->clients[i])
        {
            client_slot = i;
            slot_found = 1;
        }
    }

    return client_slot;
}

static int findFreeClientSlot(const DiagnosticsServerPtr server)
{
    return matchControlledClientByPointer(server, NULL);
}

static int findMatchingClientSlot(const DiagnosticsServerPtr server,
                                    const DiagnosticsClientPtr client)
{  
   return matchControlledClientByPointer(server, client);
}