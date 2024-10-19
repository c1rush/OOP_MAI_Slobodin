cmake_minimum_required(VERSION 3.10)
project(lr3)

# Указываем, что мы хотим использовать стандарт C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Флаги компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")
include_directories(include)

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

add_executable(FiguresLab 
    main.cpp
    src/trapezoid.cpp include/trapezoid.h
    src/rhombus.cpp include/rhombus.h
    src/pentagon.cpp include/pentagon.h
    src/figure_array.cpp include/figure_array.h
    src/figure.cpp include/figure.h
)
add_library(${CMAKE_PROJECT_NAME}_lib
    src/trapezoid.cpp
    src/rhombus.cpp
    src/pentagon.cpp
    src/figure_array.cpp
    src/figure.cpp
)

target_include_directories(FiguresLab PRIVATE include)
# Добавление тестов
enable_testing()

add_executable(tests test/tests01.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)


# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)