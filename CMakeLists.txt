cmake_minimum_required(VERSION 3.12)
project(AIS_ImmuneSystem)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем Google Test
add_subdirectory(googletest)

# Основная программа
add_executable(AIS_main
    AIS.cpp
    Antibody.cpp
    Simulator.cpp
)

# Тестовый исполняемый файл
add_executable(AIS_tests
    AIS_Tests.cpp  # Обратите внимание на правильное имя файла (без пробела)
    Antibody.cpp
    Simulator.cpp
)

# Линковка библиотек
target_link_libraries(AIS_tests
    PRIVATE
    gtest_main
)

# Для Windows
if(WIN32)
    target_compile_definitions(AIS_tests PRIVATE _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
endif()
