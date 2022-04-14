
add_library(isometric-lib     res_path.h
                              cleanup.h
                              game.cpp
                              texturemanager.cpp
                              gameobject.h
                              sdl_gameobject.cpp
                              player.cpp
                              npc.cpp
                              loaderparams.h
                              vector2d.cpp
                              inputhandler.cpp
                              GameState.cpp
                              GameState.h
                              GameStateMachine.cpp
                              GameStateMachine.h)

target_link_libraries(isometric-lib ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${CONAN_LIBS})

install(TARGETS isometric-lib RUNTIME DESTINATION ${BIN_DIR})
