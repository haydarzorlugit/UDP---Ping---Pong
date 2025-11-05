#include "udp_common.h"
#include "udp_server.h"
#include "udp_client.h"

int main(int argc, char *argv[])
{
    if (!udp_init())
        return 1;

    if (argc > 1 && strcmp(argv[1], "server") == 0)
        run_udp_server();
    else if (argc > 3 && strcmp(argv[1], "client") == 0 && strcmp(argv[2], "--server-ip") == 0)
        run_udp_client(argv[3], (argc > 5 && strcmp(argv[4], "--count") == 0) ? atoi(argv[5]) : 4);
    else
        printf("Kullanim:\n  %s server\n  %s client --server-ip <ip> [--count <n>]\n", argv[0], argv[0]);

    udp_cleanup();
    return 0;
}
