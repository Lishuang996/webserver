//
// Created by shuangli on 25-1-4.
//

#ifndef CONNECT_H
#define CONNECT_H
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
int connection_in_server(int port);
long getMessage(int new_socket,char *buffer,int max_bufferlen);
void sendFile(char* filename,char* fileRoute,int client_browser);
#endif //CONNECT_H
