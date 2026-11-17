cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
cmake_policy(SET CMP0000 NEW)

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
    LinearModel.cpp
    NonLinearModel.cpp
    DiffEqModel.cpp
)

# Указываем, где искать заголовочные файлы (.h)
target_include_directories(run_tests PRIVATE .)
target_link_libraries(run_tests gtest gtest_main)