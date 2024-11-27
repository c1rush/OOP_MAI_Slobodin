cmake_minimum_required(VERSION 3.10)
project(lr6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

add_executable(lab6 
    main.cpp
    src/npc.cpp
    src/visitor.cpp
    src/factory.cpp
    src/observer.cpp
    src/druid.cpp
    src/werewolf.cpp
    src/squirrel.cpp
)

target_include_directories(lab6 PRIVATE include)

enable_testing()

add_executable(lab6_test tests/test_npc.cpp
    src/npc.cpp
    src/visitor.cpp
    src/factory.cpp
    src/observer.cpp
    src/druid.cpp
    src/werewolf.cpp
    src/squirrel.cpp
)
target_include_directories(lab6_test PRIVATE include)
target_link_libraries(lab6_test PRIVATE gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND lab6_test)