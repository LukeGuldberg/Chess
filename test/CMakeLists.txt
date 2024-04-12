# CMake can download content from github
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.0
)

FetchContent_MakeAvailable(Catch2)


# test code for library
add_executable(tests test.cpp)
target_link_libraries(tests PUBLIC Catch2::Catch2WithMain gamelib)
