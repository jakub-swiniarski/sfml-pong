pong: main.o
	g++ main.o -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

main.o: main.cpp
	g++ -c main.cpp

.PHONY: clean run install uninstall

clean:
	rm *.o pong

run: pong
	./pong

install: pong assets_pong/
	cp pong /usr/bin/
	cp -r assets_pong /usr/share/

uninstall:
	rm /usr/bin/pong
	rm -rf /usr/share/assets_pong
