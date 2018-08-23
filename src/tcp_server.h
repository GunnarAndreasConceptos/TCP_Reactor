#ifndef TCP_SERVER_H
#define TCP_SERVER_H

//Make this return a handle if we want to test windows variant?
int createServerSocket(unsigned int tcp_port);

void disposeServerSocket(int server_socket);

#endif //TCP_SERVER_H