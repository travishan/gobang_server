cc=g++ -std=c++11
exe=server
obj=main.o ServerSocket.o
CFLAGS=-I.
$(exe) : $(obj)
	$(cc) -o $(exe) $(obj) $(CFLAGS)

main.o : main.cpp
	$(cc) -c main.cpp $(CFLAGS)

ServerSocket.o : ServerSocket.cpp 
	$(cc) -c ServerSocket.cpp $(CFLAGS)

clean :
	rm -rf *.o
