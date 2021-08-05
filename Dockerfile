FROM alpine:3.14 as builder

RUN apk --no-cache add \
    build-base \
    clang \
    clang-dev \
    ninja \
    git \
    openssl \
    openssl-dev \
    cmake

WORKDIR /hpftp

COPY . .

RUN mkdir build && \
    cd build && \
    cmake \
        -G Ninja \
        -D CMAKE_C_COMPILER=clang \
        -D CMAKE_CXX_COMPILER=clang++ \
        -D CMAKE_CXX_FLAGS="-Wno-everything" \
        -D CMAKE_BUILD_TYPE=Release \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        .. && \
    ninja && ninja install

CMD ["hpftp"]