cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -Werror -pedantic -std=c++14")

include_directories(include/og2)

set(SRC
  src/app.cc
  src/canvas.cc
  src/color.cc
  src/fonts-manager.cc
  src/images-cache.cc
  src/mouse.cc
  src/path.cc
  src/rect.cc
  src/text-cache.cc
  src/texture-infos.cc
  src/time.cc
  src/window.cc
)

add_library(og2 SHARED ${SRC})
target_link_libraries(og2 SDL2 SDL2_image SDL2_ttf)

set(TESTS_SRC
  tests/main.cc
  tests/my-win.cc
)


add_executable(check.out EXCLUDE_FROM_ALL ${TESTS_SRC})
add_dependencies(check.out og2)
target_link_libraries(check.out og2)


add_custom_target(check
  COMMAND ./check.out
)
add_dependencies(check check.out)

add_custom_target(vg
  COMMAND valgrind --track-fds=yes ./check.out
)
add_dependencies(vg check.out)

install(TARGETS og2
        LIBRARY DESTINATION lib)
install(DIRECTORY include/og2 DESTINATION include)
