run: main.o
	g++ main.o -o run

main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm *.o run
