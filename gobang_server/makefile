cc=g++ -std=c++11
exe=server
obj=main.o ServerSocket.o
CFLAGS=-ISDL2
$(exe) : $(obj)
	$(cc) -o $(exe) $(obj) $(CFLAGS)

main.o : main.cpp ServerSocket.h
	$(cc) -c main.cpp $(CFLAGS)

ServerSocket.o : ServerSocket.cpp ServerSocket.h
	$(cc) -c ServerSocket.cpp $(CFLAGS)

clean :
	rm -rf *.o
