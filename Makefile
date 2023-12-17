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
	cp pong /usr/local/bin/
	cp -r assets_pong /usr/local/share/

uninstall:
	rm /usr/local/bin/pong
	rm -rf /usr/local/share/assets_pong
