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

OBJECTS = window.o renderer.o image.o input.o \
		  image_component.o time.o tigr.c main.o \
		  world.o physics_system.o render_system.o \
		  entity.o platformer_system.o tweaker.o \
		  flipbook_component.o flipbook_system.o \
		  entity_factory.o assets.o bullet_system.o \
		  player_system.o ground_mover_system.o \
		  remove_after_duration_system.o health_system.o \
		  health_component.o logger.o tilemap.o level.o

game: $(OBJECTS)
	g++ $^ -g -o $@ -std=c++17 $(LDFLAGS)

%.o: %.cpp
	g++ -MMD -MP -c $< -o $@ -g -std=c++17

-include *.d
