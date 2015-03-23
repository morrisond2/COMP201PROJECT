CC=g++
UNAME=$(shell uname -s)
CFLAGS=-c -g -Wall -Dmain=SDL_main
# Mac OS X Users: Remove -lmingw32 and remove  -w -Wl,-subsystem,windows (DONE)
ifeq ($(UNAME),Darwin)
LDFLAGS=-I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
else
LDFLAGS=-I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
endif
SOURCES=model.cpp view.cpp controller.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=final.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) -g $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm $(EXECUTABLE)
