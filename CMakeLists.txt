cmake_minimum_required(VERSION 3.21.2)

project(Space-Invaders)

set(DEPS_DIR ${CMAKE_SOURCE_DIR}/build/external)

add_subdirectory(external/SDL2)

add_subdirectory(external/SDL2_image)

add_subdirectory(external/SDL2_mixer)

file(GLOB SI_SOURCE_FILES src/*.cpp)
file(GLOB SI_HEADER_FILES include/*.h)
  
add_executable(Space-Invaders ${SI_SOURCE_FILES} ${SI_HEADER_FILES})

target_include_directories(Space-Invaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/include/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2_image/
                                            ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2_mixer/include/)

target_link_libraries(Space-Invaders SDL2 SDL2main SDL2_image SDL2_mixer)

add_custom_command(TARGET Space-Invaders POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${DEPS_DIR}/SDL2/Debug/SDL2d.dll"
                    "${DEPS_DIR}/SDL2_image/Debug/SDL2_imaged.dll"
                    "${DEPS_DIR}/SDL2_mixer/Debug/SDL2_mixerd.dll"
                    $<TARGET_FILE_DIR:Space-Invaders>)

add_custom_command(TARGET Space-Invaders POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:Space-Invaders>/res)