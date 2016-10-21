cc=g++ -std=c++11
exe=server
obj=main.o
$(exe) : $(obj)
	$(cc) -o $(exe) $(obj)

main.o : main.cpp
	$(cc) -c main.cpp


clean :
	rm -rf *.o
