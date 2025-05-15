cmake_minimum_required(VERSION 3.12)
project(AIS_ImmuneSystem)
include(FetchContent) #Изменения

FetchContent_Declare( #Изменения 
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
#Все исходники 
file(GLOB SOURCES "AIS/*.cpp")
# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем Google Test
add_subdirectory(googletest)

# Указываем путь к исходным файлам
set(SOURCE_DIR AIS)

# Основная программа
add_executable(AIS_main
    ${SOURCE_DIR}/AIS.cpp
    ${SOURCE_DIR}/Antibody.cpp
    ${SOURCE_DIR}/Simulator.cpp
)

# Тестовый исполняемый файл
add_executable(AIS_tests
    ${SOURCE_DIR}/AIS_Tests.cpp
    ${SOURCE_DIR}/Antibody.cpp
    ${SOURCE_DIR}/Simulator.cpp
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
