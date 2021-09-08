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
		  input.hpp time.hpp tigr.h rect.hpp vec2.hpp \
		  world.hpp body_component.hpp image_component.hpp \
		  physics_system.hpp render_system.hpp entity.hpp \
		  platformer_system.hpp platformer_component.hpp \
		  tweaker.hpp flipbook.hpp flipbook_component.hpp \
		  flipbook_system.hpp entity_factory.hpp \
		  assets.hpp bullet_component.hpp bullet_system.hpp \
		  player_component.hpp player_system.hpp

SOURCES = window.cpp renderer.cpp image.cpp input.cpp \
		  image_component.cpp time.cpp tigr.c main.cpp \
		  world.cpp physics_system.cpp render_system.cpp \
		  entity.cpp platformer_system.cpp tweaker.cpp \
		  flipbook_component.cpp flipbook_system.cpp \
		  entity_factory.cpp assets.cpp bullet_system.cpp \
		  player_system.cpp

game: $(HEADERS) $(SOURCES)
	g++ $(SOURCES) -g -o $@ -std=c++17 $(LDFLAGS)
