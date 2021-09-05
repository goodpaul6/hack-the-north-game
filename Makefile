ifeq ($(OS),Windows_NT)
	LDFLAGS = -lopengl32 -lgdi32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -framework OpenGL -framework Cocoa
	else ifeq ($(UNAME_S),Linux)
		LDFLAGS = -lGLU -lGL -lX11
	endif
endif

HEADERS = color.hpp window.hpp renderer.hpp image.hpp \
		  input.hpp time.hpp tigr.h rect.hpp vec2.hpp

SOURCES = window.cpp renderer.cpp image.cpp input.cpp \
		  time.cpp tigr.c main.cpp

game: $(HEADERS) $(SOURCES)
	g++ $(SOURCES) -g -o $@ -std=c++17 $(LDFLAGS)
