pong: main.o
	g++ main.o -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp
	g++ -c main.cpp

.PHONY: clean run install uninstall

clean:
	rm *.o pong

run: pong
	./pong

install: pong res
	mkdir -p /usr/local/share/pong/
	cp pong /usr/local/bin
	cp res/* /usr/local/share/pong/

uninstall:
	rm /usr/local/bin/pong
	rm -rf /usr/local/share/pong
