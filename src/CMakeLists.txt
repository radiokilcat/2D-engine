add_executable(isometric-game main.cpp)

target_include_directories(isometric-game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(isometric-game isometric-lib)
