#pragma once

#include <uv.h>

#include <functional>
#include <string>

class Socket {
public:
    Socket(std::string address, unsigned short port);
    ~Socket();

public:
    void Init();
    void Run();

private:
    static void AcceptConnection(uv_stream_t *server, int status);
    static void AsyncCloseCallback(uv_async_t *handle);
    static void StartThread(void *pSocket);

private:
    void RunServer(int status = UV_RUN_DEFAULT);

private:
    uv_tcp_t server{};
    uv_loop_t loop;
    uv_mutex_t mutexClients;
    uv_async_t asyncCloseHandle;
    uv_thread_t threadHandle;

private:
    std::string address;
    unsigned short port;
    sockaddr_in addr;
    int backlog;
};