all: build execute
build:
	gcc *.c -o debug/result
execute:
	./debug/result