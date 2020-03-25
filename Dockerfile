# Сборка
FROM gcc:latest AS build

RUN apt-get update && \
    apt-get install -y cmake

COPY . /usr/src/FTPServer
WORKDIR /usr/src/FTPServer/dist

# This command compiles your app using GCC, adjust for your source code
RUN cmake ../../FTPServer && \
    cmake --build .

# В качестве базового образа используем ubuntu:latest
FROM ubuntu:latest

# Установим рабочую директорию нашего приложения
WORKDIR /usr/src/FTPServer/dist

# Скопируем приложение со сборочного контейнера в рабочую директорию
COPY --from=build /usr/src/FTPServer/dist .

EXPOSE 8051
# Установим точку входа
ENTRYPOINT ["./FTPServer"]
