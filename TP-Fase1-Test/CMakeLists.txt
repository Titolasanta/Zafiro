cmake_minimum_required(VERSION 3.12)
project(TP-Fase1-Test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TP-Fase1-Test_SOURCE_DIR}/cmake")

file(GLOB helloworld_SRC
        "Vista/*.h"
        "Vista/*.cpp"
        "Modelo/*.h"
        "Modelo/*.cpp"
        )

set(SOURCE_FILES ${helloworld_SRC} Vista/SpriteRojo.cpp Vista/SpriteRojo.h Vista/Personajes.cpp Vista/Personajes.h  Vista/View.cpp Vista/View.h  Vista/Pasto.cpp Vista/Pasto.h Vista/Piedra.cpp Vista/Piedra.h Vista/Viewable.cpp Vista/Viewable.h Vista/Controler.cpp Vista/Controler.h)



add_executable(TP-Fase1-Test ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
        ${CMAKE_BINARY_DIR}

        "/home/tito/Desktop/Tallar/github/TP-Fase1-Test/Modelo"
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR} )

target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

