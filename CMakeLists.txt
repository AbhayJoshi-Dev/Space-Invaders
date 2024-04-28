cmake_minimum_required(VERSION 3.25.0)

project(Space-Invaders
    LANGUAGES C CXX
    VERSION 1.0
)

set(DEPS_DIR ${CMAKE_SOURCE_DIR}/build/external)

# Check that git submodules were cloned
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external//SDL2/CMakeLists.txt")
  message("${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/CMakeLists.txt")
  message(FATAL_ERROR "Please initialize submodules using:\n  git submodule update --init --recursive")
endif()


set(BUILD_SHARED_LIBS ON CACHE BOOL "Link to libs dynamically")

### SDL
if (NOT BUILD_SHARED_LIBS)
    set(SDL_SHARED_ENABLED_BY_DEFAULT OFF CACHE BOOL "Don't build SDL as shared library")
endif()
option(SDL_TEST "Build the SDL2_test library" OFF)
add_subdirectory(external/SDL2)



### SDL_image
option(SDL2IMAGE_PNG "Support loading PNG Image" ON)

# don't need the rest
option(SDL2IMAGE_SAMPLES "Build the SDL2_image sample program(s)" OFF)
option(SDL2IMAGE_INSTALL "Enable SDL2_image install target" OFF)
option(SDL2IMAGE_DEPS_SHARED "Load dependencies dynamically" OFF)
option(SDL2IMAGE_SAMPLES "Build the SDL2_image sample program(s)" OFF)
option(SDL2IMAGE_BMP "Support loading BMP images" OFF)
option(SDL2IMAGE_GIF "Support loading GIF images" OFF)
option(SDL2IMAGE_JPG "Support loading JPEG images" OFF)
option(SDL2IMAGE_LBM "Support loading LBM images" OFF)
option(SDL2IMAGE_PCX "Support loading PCX images" OFF)
option(SDL2IMAGE_PNM "Support loading PNM images" OFF)
option(SDL2IMAGE_QOI "Support loading QOI images" OFF)
option(SDL2IMAGE_SVG "Support loading SVG images" OFF)
option(SDL2IMAGE_TGA "Support loading TGA images" OFF)
option(SDL2IMAGE_XCF "Support loading XCF images" OFF)
option(SDL2IMAGE_XPM "Support loading XPM images" OFF)
option(SDL2IMAGE_XV "Support loading XV images" OFF)
add_subdirectory(external/SDL2_image)


### SDL_mixer
option(SDL2MIXER_INSTALL "Enable SDL2mixer install target" OFF)
option(SDL2MIXER_DEPS_SHARED "Default value for loading dependencies dynamically" OFF)
option(SDL2MIXER_SAMPLES "Build the SDL2_mixer sample program(s)" OFF)
option(SDL2MIXER_CMD "Support an external music player" OFF)
option(SDL2MIXER_FLAC "Enable FLAC music" OFF)
option(SDL2MIXER_MOD "Support loading MOD music" OFF)
option(SDL2MIXER_MP3 "Enable MP3 music" OFF)
option(SDL2MIXER_MIDI "Enable MIDI music" OFF)
option(SDL2MIXER_OPUS "Enable Opus music" OFF)
option(SDL2MIXER_WAVPACK "Enable WavPack music" OFF)
add_subdirectory(external/SDL2_mixer)

### SDL_ttf
option(SDL2TTF_SAMPLES "Build the SDL2_ttf sample program(s)" OFF)
option(SDL2TTF_INSTALL "Enable SDL2_ttf install target" OFF)
option(SDL2TTF_VENDORED "Use vendored third-party libraries" ON)
add_subdirectory(external/SDL_ttf)



file(GLOB SOURCE_FILES src/*.cpp)
  
add_executable(Space-Invaders ${SOURCE_FILES})

target_include_directories(Space-Invaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2_image/include
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2_mixer/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_ttf/)


if(BUILD_SHARED_LIBS)
  target_link_libraries(Space-Invaders PUBLIC
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
  )
else()
  target_link_libraries(Space-Invaders PUBLIC
    SDL2::SDL2-static
    SDL2::SDL2main
    SDL2_image::SDL2_image-static
    SDL2_ttf::SDL2_ttf-static
    SDL2_mixer::SDL2_mixer-static
  )
endif()

if(BUILD_SHARED_LIBS)
    add_custom_command(TARGET Space-Invaders POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                      $<TARGET_FILE:SDL2>
                      $<TARGET_FILE:SDL2_image>
                      $<TARGET_FILE:SDL2_mixer>
                      $<TARGET_FILE:SDL2_ttf>
                      $<TARGET_FILE_DIR:Space-Invaders>)
endif()

add_custom_command(TARGET Space-Invaders POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Space-Invaders>/res)