cmake_minimum_required(VERSION 3.20)
project(Task02)

set(CMAKE_CXX_STANDARD 17)

# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Собираем тесты
add_executable(run_tests
    ../test/test_models.cpp
    ../../task_01/src/LinearModel.cpp
    ../../task_01/src/NonLinearModel.cpp
    ../../task_01/src/DiffEqModel.cpp
)

target_include_directories(run_tests PRIVATE ../../task_01/src)
target_link_libraries(run_tests gtest gtest_main)