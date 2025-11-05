#include "udp_server.h"

int run_udp_server()
{
    SOCKET s;
    struct sockaddr_in server, client;
    char buf[BUF_SIZE];
    int client_len = sizeof(client), recv_len;

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET) {
        udp_perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SERVER_PORT);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        udp_perror("bind");
        closesocket(s);
        return 1;
    }

    printf("UDP server listening on port %d...\n", SERVER_PORT);

    while (1)
    {
        recv_len = recvfrom(s, buf, BUF_SIZE - 1, 0, (struct sockaddr *)&client, &client_len);
        if (recv_len == SOCKET_ERROR) {
            udp_perror("recvfrom");
            continue;
        }

        buf[recv_len] = '\0';
        printf("Came: %s (from %s:%d)\n", buf, inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        char reply[BUF_SIZE];
        if (strncmp(buf, "PING", 4) == 0) {
            const char *tail = buf + 4;
            while (*tail == ' ') tail++;
            snprintf(reply, sizeof(reply), "PONG %s", *tail ? tail : "0");
        } else {
            snprintf(reply, sizeof(reply), "%s", buf);
        }

        int sent = sendto(s, reply, (int)strlen(reply), 0, (struct sockaddr *)&client, client_len);
        if (sent == SOCKET_ERROR)
            udp_perror("sendto");
        else
            printf("Sent: %s\n", reply);
    }

    closesocket(s);
    return 0;
}
