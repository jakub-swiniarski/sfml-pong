SRC = $(wildcard src/*.cpp)
HDR = $(wildcard src/*.hpp)
OBJ = $(patsubst src/%.cpp, %.o, $(SRC))

all: pong

%.o: src/%.cpp
	g++ -c -O2 -DDEBUG $<

$(OBJ): $(HDR)

pong: $(OBJ)
	g++ -o $@ $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run: all
	./pong

clean:
	rm -f *.o pong

install: all
	mkdir -p /usr/local/share/pong/
	cp -f pong /usr/local/bin/
	cp -f res/* /usr/local/share/pong/

uninstall:
	rm -f /usr/local/bin/pong
	rm -rf /usr/local/share/pong

.PHONY: all run clean install uninstall
