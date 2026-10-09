# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# ВАЖНО: заставляем Google Test использовать динамическую библиотеку (MDd), как и весь проект
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Создаем исполняемый файл для тестов
add_executable(run_tests
    ../test/test_models.cpp
    ../../task_01/src/LinearModel.cpp
    ../../task_01/src/NonLinearModel.cpp
    ../../task_01/src/DiffEqModel.cpp
)

# Указываем, где искать заголовочные файлы (.h)
target_include_directories(run_tests PRIVATE ../../task_01/src)

# Привязываем Google Test
target_link_libraries(run_tests gtest gtest_main)
# Делаем так, чтобы Visual Studio видела наши тесты
enable_testing()
add_test(NAME AllTests COMMAND run_tests)