# UDP Ping-Pong Server & Client (Windows)


This project is a UDP-based Ping-Pong server and client application written for Windows using Winsock2.
The server processes incoming messages, responding with PONG to PING messages and echoing back unknown messages.
The client sends PING messages to the server, measures RTT (Round-Trip Time), and prints the responses.

# Features

## Server:
- Sends `PONG <queue> <timestamp>` in response to PING messages.
- Sends back unknown messages as echo.
- Logs UDP socket buffer sizes (`SO_SNDBUF` / `SO_RCVBUF`)
## Client:
- Sets the server IP address with `--server-ip <IP>`.
- Sets the number of PINGs to be sent with `--count <n>` (default: 4).
- Adds a sequence number and timestamp to each PING message.
- Calculates RTT (Round-Trip Time)
- 1-second response timeout

# Notes

- The program was developed with Winsock2 on Windows.
- For long-term tests, using GetTickCount64() is recommended for measuring RTT.
- When exiting the server with Ctrl+C, the socket must be closed properly.

# Development Plan

- IPv6 support will be added.
- More advanced logging and error handling will be added.
- Client timeout and retry mechanisms can be improved.