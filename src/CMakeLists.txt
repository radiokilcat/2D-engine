find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(isometric-game main.cpp res_path.h cleanup.h)
target_link_libraries(isometric-game ${SDL2_LIBRARIES} )
install(TARGETS isometric-game RUNTIME DESTINATION ${BIN_DIR})
