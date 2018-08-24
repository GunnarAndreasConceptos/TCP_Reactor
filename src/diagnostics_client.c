#include "diagnostics_client.h"
#include "event_handler.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
struct DiagnosticsClient
{
    Handle client_socket;
    EventHandler event_handler;

    ServerEventNotifier event_notifier;
};

#define MAX_MESSAGE_SIZE 1024

static Handle acceptClientConnection(int server_handle);
static Handle getClientSocket(void* instance);
static void handleReadEvent(void *instance);

static Handle getClientSocket(void* instance)
{
    const DiagnosticsClientPtr client = instance;
    return client->client_socket;
}

static void handleReadEvent(void* instance)
{
    const DiagnosticsClientPtr client = instance;
    char diagnostic_message[MAX_MESSAGE_SIZE] = {0};

    const ssize_t recieve_result = recv(client->client_socket, diagnostic_message, sizeof diagnostic_message, 0);

    if (0 < recieve_result)
    {
        (void) printf("Client: Diagnostics received - %s\n", diagnostic_message);
    }
    else
    {
        client->event_notifier.on_client_closed(client->event_notifier.server, client);
    }
}

//Implemention of ADT functions
DiagnosticsClientPtr createClient(Handle server_handle, const ServerEventNotifier* event_notifier)
{
    if (NULL == event_notifier)
    {
        return NULL;
    }

    DiagnosticsClientPtr client = malloc(sizeof *client);

    if (NULL != client)
    {
        client->client_socket = acceptClientConnection(server_handle);
        client->event_handler.instance = client;
        client->event_handler.get_handle = getClientSocket;
        client->event_handler.handle_event = handleReadEvent;

        //TODO: Register event handler
        client->event_notifier = *event_notifier;
    }

    return client;
}

void destroyClient(DiagnosticsClientPtr client)
{
    //TODO: Unregister
    close(client->client_socket);
    free(client);
}

static Handle acceptClientConnection(int server_handle)
{
    struct sockaddr_in client_address = {0};
   
   socklen_t address_size = sizeof client_address;

   const Handle client_handle = accept(server_handle, (struct sockaddr*) &client_address, &address_size);
   
   if(0 > client_handle) {
      /* NOTE: In the real world, this function should be more forgiving.
      For example, the client should be allowed to abort the connection request. */
      printf("Failed to accept client connection");
      return client_handle;
   }
   
   (void) printf("Client: New connection created on IP-address %X\n", ntohl(client_address.sin_addr.s_addr));
   
   return client_handle;
}