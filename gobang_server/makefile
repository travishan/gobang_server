cc=g++ -std=c++11
exe=server
obj=main.o ServerSocket.o
CFLAGS=-lSDL2 -lSDL2_net

$(exe) : $(obj)
	$(cc) -o $(exe) $(obj) $(CFLAGS)

main.o : main.cpp
	$(cc) -c main.cpp

ServerSocket.o : ServerSocket.cpp
	$(cc) -c ServerSocket.cpp

clean :
	rm -rf *.o
