#include <socket.h>

#include <utility>

Socket::Socket(std::string address, unsigned short port) {
    this->address = std::move(address);
    this->port = port;
}

Socket::~Socket() {
    if (loop) {
        uv_loop_close(loop);
        free(loop);
    }
}

void Socket::InitSocket() {
    loop = uv_default_loop();
    uv_tcp_init(loop, &server);
    uv_ip4_addr(address.c_str(), port, &addr);

    int r = uv_listen((uv_stream_t *) &server, 128, onNewConnectionCb);
}

void Socket::OnNewConnection(void (*callback)(uv_stream_t *, int)) {
    onNewConnectionCb = callback;
}
