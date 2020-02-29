CLIENTFILES=client.cpp
SERVERFILES=server.cpp

all: server execute
server:
	g++ $(SERVERFILES) -o debug/server
client:
	g++ $(CLIENTFILES) -o debug/client
execute:
	./debug/server