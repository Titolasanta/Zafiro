cmake_minimum_required(VERSION 3.12)
project(TP-Fase1-Test)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${TP-Fase1-Test_SOURCE_DIR}/cmake")



find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

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

set(tSOURCE_FILES_S ${tserver_SRC} server/Interpreter.cpp server/Interpreter.h server/Sender.cpp server/Sender.h server/xmlServer.cpp server/xmlServer.h server/SignalReceiver.cpp server/SignalReceiver.h server/SignalChecker.cpp server/SignalChecker.h)
set(tSOURCE_FILES_C ${tclient_SRC} client/FullHouse.cpp client/FullHouse.h client/Verifier.cpp client/Verifier.h client/InvalidLogin.cpp client/InvalidLogin.h client/Quit.cpp client/Quit.h client/lifeSupport.cpp client/lifeSupport.h)


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