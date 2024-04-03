SRC = $(wildcard src/*.cpp)
HDR = $(wildcard src/*.hpp)
OBJ = $(patsubst src/%.c, %.o, $(SRC))

pong: $(OBJ)
	g++ -o $@ $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(OBJ): $(SRC) $(HDR)
	gcc -c $(SRC) -O2

.PHONY: clean run install uninstall

clean:
	rm *.o pong

run: pong
	./pong

install: pong res
	mkdir -p /usr/local/share/pong/
	cp pong /usr/local/bin/
	cp res/* /usr/local/share/pong/

uninstall:
	rm /usr/local/bin/pong
	rm -rf /usr/local/share/pong
