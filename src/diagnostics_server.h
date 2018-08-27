#ifndef DIAGNOSTICS_SERVER_H
#define DIAGNOSTICS_SERVER_H

//Incomplete type for FIRST-CLASS ADT. Used to hide struct internals from other modules.
typedef struct DiagnosticsServer *DiagnosticsServerPtr;

//Returns NULL if failed
DiagnosticsServerPtr createServer(unsigned int tcpPort);

//Send in pointer of pointer so that we can NULL the pointer and test that it actually has been NULLed
void destroyServer(DiagnosticsServerPtr server);
#endif