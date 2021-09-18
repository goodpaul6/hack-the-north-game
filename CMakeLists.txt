cmake_minimum_required(VERSION 3.2.3 FATAL_ERROR)

project(hack-the-north-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /permissive-")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:console")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

set(SOURCES
    window.cpp
    renderer.cpp
    image.cpp
    input.cpp
    image_component.cpp
    time.cpp
    tigr.c
    main.cpp
    world.cpp
    physics_system.cpp
    render_system.cpp
    entity.cpp
    platformer_system.cpp
    tweaker.cpp
    flipbook_component.cpp
    flipbook_system.cpp
    entity_factory.cpp
    assets.cpp
    bullet_system.cpp
    player_system.cpp
    ground_mover_system.cpp
    remove_after_duration_system.cpp
    health_system.cpp
    health_component.cpp
    logger.cpp
    tilemap.cpp
    level.cpp
    particle_manager.cpp
    particle_emitter_system.cpp
    top_down_system.cpp
    sand.cpp)

add_executable(game ${SOURCES})

if(WIN32)
    target_link_libraries(game PRIVATE opengl32.lib gdi32.lib)
elseif(APPLE)
    target_link_libraries(game PRIVATE "-framework OpenGL" "-framework Cocoa")
else()
    target_link_libraries(game PRIVATE GLU GL X11)
endif()
