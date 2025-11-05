cmake_minimum_required(VERSION 3.20)
project(udp_ping C)

set(CMAKE_C_STANDARD 11)

add_executable(udp_ping
        main.c
        udp_client.c
        udp_server.c
        udp_common.c
)


target_link_libraries(udp_ping ws2_32)
