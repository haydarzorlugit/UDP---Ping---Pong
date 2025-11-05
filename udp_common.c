#include "udp_common.h"

int udp_init() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock init failed: %d\n", WSAGetLastError());
        return 0;
    }
    return 1;
}

void udp_cleanup() {
    WSACleanup();
}

void udp_perror(const char *msg) {
    printf("%s: hata kodu %d\n", msg, WSAGetLastError());
}

void udp_log_socket_buffers(SOCKET s) {
    int sndbuf = 0, rcvbuf = 0, len = sizeof(int);
    getsockopt(s, SOL_SOCKET, SO_SNDBUF, (char *)&sndbuf, &len);
    getsockopt(s, SOL_SOCKET, SO_RCVBUF, (char *)&rcvbuf, &len);
    printf("SO_SNDBUF = %d bytes, SO_RCVBUF = %d bytes\n", sndbuf, rcvbuf);
}
