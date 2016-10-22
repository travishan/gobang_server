cc=g++ -std=c++11
exe=server
obj=main.o ServerSocket.o
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

$(exe) : $(obj)
	$(cc) -o $(exe) $(obj) $(SDL_LDFLAGS)

main.o : main.cpp ServerSocket.h
	$(cc) -c main.cpp $(SDL_CFLAGS)

ServerSocket.o : ServerSocket.cpp ServerSocket.h
	$(cc) -c ServerSocket.cpp $(SDL_CFLAGS)

clean :
	rm -rf *.o
