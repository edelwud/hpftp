all: build execute
build:
	g++ *.cpp -o debug/result
execute:
	./debug/result