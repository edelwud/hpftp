#include <socket.h>

#include <utility>

#include <exceptions/address_conversion.h>
#include <exceptions/bind_exception.h>
#include <exceptions/listen_exception.h>

Socket::Socket(std::string address, unsigned short port) {
    this->address = std::move(address);
    this->port = port;
}

Socket::~Socket() {
    uv_loop_close(&loop);
}

void Socket::Init() {
    if (uv_loop_init(&loop)) {
        throw InternalException();
    }

    if (uv_mutex_init(&mutexClients)) {
        throw InternalException();
    }

    if (uv_async_init(&loop, &asyncCloseHandle, AsyncCloseCallback)) {
        throw InternalException();
    }
    asyncCloseHandle.data = this;

    if (uv_tcp_init(&loop, &server)) {
        throw InternalException();
    }
    server.data = this;

    if (uv_tcp_nodelay(&server, true)) {
        throw InternalException();
    }

    if (uv_ip4_addr(address.c_str(), port, &addr)) {
        throw AddressConversion();
    }

    if (uv_tcp_bind(&server, (sockaddr *) &addr, 0)) {
        throw BindException();
    }

    if (uv_listen((uv_stream_t *) &server, backlog, AcceptConnection)) {
        throw ListenException();
    }
}

void Socket::AcceptConnection(uv_stream_t *server, int status) {
}

void Socket::Run() {
    uv_thread_create(&threadHandle, StartThread, this);
}

void Socket::AsyncCloseCallback(uv_async_t *handle) {
    auto socket = (Socket *) handle->data;
}

void Socket::StartThread(void *pSocket) {
    auto socket = (Socket *) pSocket;
    socket->RunServer();
}

void Socket::RunServer(int status) {
    if (uv_run(&loop, (uv_run_mode) status)) {
        throw InternalException();
    }
}
