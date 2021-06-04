find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(isometric-game main.cpp
                              res_path.h
                              cleanup.h
                              game.cpp
                              texturemanager.cpp
                              gameobject.cpp
                              player.cpp
                              npc.cpp
                              )

target_link_libraries(isometric-game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY})

install(TARGETS isometric-game RUNTIME DESTINATION ${BIN_DIR})
