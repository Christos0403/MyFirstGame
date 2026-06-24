CFLAGS = $(shell pkg-config --cflags raylib)
LIBS = $(shell pkg-config --libs raylib)

run:
	g++ game.cpp -o game $(CFLAGS) $(LIBS)
	./game

clean:
	rm game