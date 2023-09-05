pong: main.o
	g++ main.o -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp
	g++ -c main.cpp

.PHONY: clean run

clean:
	rm *.o pong

run:
	./pong
