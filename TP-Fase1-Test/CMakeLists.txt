cmake_minimum_required(VERSION 3.12)
project(TP-Fase1-Test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TP-Fase1-Test_SOURCE_DIR}/cmake")


INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(
        ${CMAKE_BINARY_DIR}

        "/home/tito/Desktop/Tallar/github/TP-Fase1-Test/Modelo"
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})


file(GLOB tserver_SRC
        "server/*"
        "common/*"
        )

file(GLOB tclient_SRC
        "client/*"
        "common/*"
        )

set(tSOURCE_FILES_S ${tserver_SRC} )
set(tSOURCE_FILES_C ${tclient_SRC} client/Sound.cpp client/Sound.h)


add_executable(tServer ${tSOURCE_FILES_S})

add_executable(tClient ${tSOURCE_FILES_C})


target_link_libraries(tClient
        SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread)

target_link_libraries(tServer
        SDL2 SDL2_image SDL2_mixer SDL2_ttf pthread)