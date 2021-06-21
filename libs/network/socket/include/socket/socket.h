#pragma once

#include <uv.h>

#include <functional>
#include <string>

class Socket {
public:
    Socket(std::string address, unsigned short port);
    ~Socket();

public:
    void InitSocket();
    void OnNewConnection(void (*callback)(uv_stream_t *, int));

private:
    void (*onNewConnectionCb)(uv_stream_t *, int);

private:
    uv_tcp_t server{};
    uv_loop_t *loop{};

private:
    std::string address;
    unsigned short port;
    sockaddr_in addr;
};