#ifndef UDP_COMMON_H
#define UDP_COMMON_H

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 9999
#define BUF_SIZE 1024

// Start/Clear capacity
int udp_init();
void udp_cleanup();

// Error printing aids
void udp_perror(const char *msg);

// Show socket buffer sizes
void udp_log_socket_buffers(SOCKET s);

#endif
