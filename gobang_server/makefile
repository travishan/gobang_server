cc=g++ -std=c++11
exe=server
obj=main.o ServerSocket.o Referee.o Player.o Room.o House.o
CFLAGS=-lSDL2 -lSDL2_net

$(exe) : $(obj)
	$(cc) -o $(exe) $(obj) $(CFLAGS)

main.o : main.cpp
	$(cc) -c main.cpp

ServerSocket.o : ServerSocket.cpp
	$(cc) -c ServerSocket.cpp

Referee.o : Referee.cpp
	$(cc) -c Referee.cpp

Player.o : Player.cpp
	$(cc) -c Player.cpp

Room.o : Room.cpp
	$(cc) -c Room.cpp

House.o : House.cpp
	$(cc) -c House.cpp

clean :
	rm -rf *.o
