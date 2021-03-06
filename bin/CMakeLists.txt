cmake_minimum_required(VERSION 2.8.9)
project (neural_network)

option(sixty "sixty" OFF)
option(debug "debug" OFF)
option(windows "windows" OFF)
option(crosscompile "crosscompile" OFF)

if (windows)
	message("Building for Windows")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (crosscompile)
	message("Cross compiling for Windows")
	if (sixty)
		set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
	else()
		set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-static-libgcc -static-libstdc++ -static")
else()
	message("Building for Linux")
	set(CMAKE_CXX_COMPILER clang++)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
endif()

if ((crosscompile OR windows) AND sixty)
	set(SDL2_PATH              "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/x86_64-w64-mingw32")
	set(SDL2_INCLUDE_DIR       "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/x86_64-w64-mingw32/include")	
	set(SDL2_LIBRARY           "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/x86_64-w64-mingw32/lib/libSDL2.dll.a")
	set(SDL2_IMAGE_LIBRARY     "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/x86_64-w64-mingw32/lib/libSDL2_image.dll.a")
	set(SDL2_TTF_LIBRARY       "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a")
	set(SDL2_MAIN              "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/x86_64-w64-mingw32/lib/libSDL2main.a")
elseif (crosscompile OR windows)
	set(SDL2_PATH              "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/i686-w64-mingw32")
	set(SDL2_INCLUDE_DIR       "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/i686-w64-mingw32/include")	
	set(SDL2_LIBRARY           "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/i686-w64-mingw32/lib/libSDL2.dll.a")
	set(SDL2_IMAGE_LIBRARY     "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/i686-w64-mingw32/lib/libSDL2_image.dll.a")
	set(SDL2_TTF_LIBRARY       "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/i686-w64-mingw32/lib/libSDL2_ttf.dll.a")
	set(SDL2_MAIN              "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/i686-w64-mingw32/lib/libSDL2main.a")
	set(SDL2_IMAGE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../libs/SDL2-2.0.4/i686-w64-mingw32/include")
endif()

if (debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/../cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES ../src/*.cpp ../src/*.hpp)

if (windows)
	add_executable(NeuralNetwork ${SOURCES})
	target_link_libraries(NeuralNetwork -lmingw32 ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})
elseif (crosscompile)
	add_executable(NeuralNetwork.exe ${SOURCES})
	target_link_libraries(NeuralNetwork.exe -lmingw32 ${SDL2_MAIN} ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})
else()
	add_executable(neural_network ${SOURCES})
	target_link_libraries(neural_network ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})
endif()
