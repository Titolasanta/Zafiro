cmake_minimum_required(VERSION 3.12)



project(github)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)


include_directories(.)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeModules/")


find_package(SDL2TTF REQUIRED)
find_package(SDL2_image REQUIRED)






add_executable(github
        clienteEstado.h
        clienteMain.cpp
        commonButton.cpp
        commonButton.h
        commonException.cpp
        commonException.h
        commonImgTexture.cpp
        commonImgTexture.h
        commonSDLException.cpp
        commonSDLException.h
        commonSDLIMGException.cpp
        commonSDLIMGException.h
        commonSdlImgInit.cpp
        commonSdlImgInit.h
        commonSdlInit.cpp
        commonSdlInit.h
        commonSDLTTFException.cpp
        commonSDLTTFException.h
        commonSdlTtfInit.cpp
        commonSdlTtfInit.h
        commonSocket.cpp
        commonSocket.h
        commonTextTexture.cpp
        commonTextTexture.h
        commonTexture.cpp
        commonTexture.h
        commonWindow.cpp
        commonWindow.h
        )

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})