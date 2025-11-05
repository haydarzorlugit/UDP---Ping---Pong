#include "udp_client.h"

int run_udp_client(const char *server_ip, int count)
{
    SOCKET s;
    struct sockaddr_in server;
    char buf[BUF_SIZE];
    int server_len = sizeof(server);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET) {
        udp_perror("socket");
        return 1;
    }

    DWORD timeout_ms = 1000;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout_ms, sizeof(timeout_ms));

    udp_log_socket_buffers(s);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_port = htons(SERVER_PORT);

    printf("Server IP: %s, Count: %d\n", server_ip, count);

    for (int i = 1; i <= count; ++i)
    {
        char msg[128];
        DWORD start = GetTickCount();

        snprintf(msg, sizeof(msg), "PING %d %lu", i, (unsigned long)start);

        int sent = sendto(s, msg, (int)strlen(msg), 0, (struct sockaddr *)&server, server_len);
        if (sent == SOCKET_ERROR) {
            udp_perror("sendto");
            break;
        }

        printf("Posted: %s\n", msg);

        int recv_len = recvfrom(s, buf, BUF_SIZE - 1, 0, (struct sockaddr *)&server, &server_len);
        if (recv_len == SOCKET_ERROR) {
            int err = WSAGetLastError();
            if (err == WSAETIMEDOUT)
                printf("Timeout (no answer)\n");
            else
                udp_perror("recvfrom");
            continue;
        }

        buf[recv_len] = '\0';
        DWORD end = GetTickCount();
        printf("Answer: %s | RTT = %lu ms\n", buf, (unsigned long)(end - start));
        Sleep(500);
    }

    closesocket(s);
    return 0;
}
