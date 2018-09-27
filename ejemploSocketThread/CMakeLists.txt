cmake_minimum_required(VERSION 3.12)
project(TP-Fase2-Test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TP-Fase1-Test_SOURCE_DIR}/cmake")

file(GLOB server_SRC
        "HelloSocket/server/*.h"
        "HelloSocket/server/*.cpp"
        "HelloSocket/common/*.h"
        "HelloSocket/common/*.cpp"
        )

file(GLOB client_SRC
        "HelloSocket/client/*.h"
        "HelloSocket/client/*.cpp"
        "HelloSocket/common/*.h"
        "HelloSocket/common/*.cpp"
        )

set(SOURCE_FILES_S ${server_SRC} )
set(SOURCE_FILES_C ${client_SRC} )


add_executable(Server ${SOURCE_FILES_S})

add_executable(Client ${SOURCE_FILES_C})



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

target_link_libraries(Server
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${pthread}
        ${SDL2_TTF_LIBRARIES})


target_link_libraries(Client
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${pthread}
        ${SDL2_TTF_LIBRARIES})


file(GLOB tserver_SRC
        "HelloThread/server/*.h"
        "HelloThread/server/*.cpp"
        "HelloThread/common/*.h"
        "HelloThread/common/*.cpp"
        )

file(GLOB tclient_SRC
        "HelloThread/client/*.h"
        "HelloThread/client/*.cpp"
        "HelloThread/common/*.h"
        "HelloThread/common/*.cpp"
        )

set(tSOURCE_FILES_S ${tserver_SRC} )
set(tSOURCE_FILES_C ${tclient_SRC} )


add_executable(tServer ${tSOURCE_FILES_S})

add_executable(tClient ${tSOURCE_FILES_C})


target_link_libraries(tClient
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${pthread}
        ${SDL2_TTF_LIBRARIES})

target_link_libraries(tServer
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${pthread}
        ${SDL2_TTF_LIBRARIES})