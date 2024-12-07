cmake_minimum_required(VERSION 3.10)
project(lr7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем корутины для Clang или GCC
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  execute_process(
    COMMAND ${CMAKE_CXX_COMPILER} -dM -E - < /dev/null
    OUTPUT_VARIABLE COMPILER_PREDEFS
  )
  if(COMPILER_PREDEFS MATCHES ".*__cpp_coroutines.*")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
  else()
    message(WARNING "Coroutines not supported by the compiler. Skipping -fcoroutines.")
  endif()
endif()

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

add_executable(lab7 
    main.cpp
    src/npc.cpp
    src/visitor.cpp
    src/factory.cpp
    src/observer.cpp
    src/logger.cpp
    src/scheduler.cpp
    src/druid.cpp
    src/werewolf.cpp
    src/squirrel.cpp
)

target_include_directories(lab7 PRIVATE include)

target_link_libraries(lab7 pthread)

enable_testing()

add_executable(lab7_test tests/test_npc.cpp
  src/npc.cpp
  src/visitor.cpp
  src/factory.cpp
  src/observer.cpp
  src/logger.cpp
  src/scheduler.cpp
  src/druid.cpp
  src/werewolf.cpp
  src/squirrel.cpp
)
target_include_directories(lab7_test PRIVATE include)
target_link_libraries(lab7_test PRIVATE gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND lab7_test)
