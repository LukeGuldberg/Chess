find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(gamelib
    chessboard.cpp
    graphics.cpp
    piece.cpp  
    engine.cpp
    agent.cpp
) 

target_include_directories(gamelib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(gamelib PUBLIC SDL2::SDL2 SDL2_image::SDL2_image)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC gamelib)
