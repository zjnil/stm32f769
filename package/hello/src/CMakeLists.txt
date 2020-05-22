cmake_minimum_required (VERSION 3.17)
project (hello C)

find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(ALSA REQUIRED)
find_package(Freetype REQUIRED)
find_package(ZLIB REQUIRED)

file(GLOB SOURCES
    main.c
    bmp_drawable.c
    drawable.c
    text_drawable.c
    window_drawable.c)

include_directories(
	include
        ${SDL_INCLUDE_DIR}
        ${SDL_TTF_INCLUDE_DIR}
)

add_executable(hello ${SOURCES})

target_link_libraries(hello
	${SDL_LIBRARY}
	${SDL_TTF_LIBRARY}
	${ALSA_LIBRARY}
	${FREETYPE_LIBRARIES}
	${ZLIB_LIBRARIES}
)
