cc=g++ -std=c++11
exe=server
obj=main.o ServerSocket.o
$(exe) : $(obj)
	$(cc) -o $(exe) $(obj)

main.o : main.cpp
	$(cc) -c main.cpp

ServerSocket.o : ServerSocket.cpp
	$(cc) -c ServerSocket.cpp


clean :
	rm -rf *.o
