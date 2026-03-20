cmake_minimum_required(VERSION 3.10)
project(lab1)

add_library(lab1_library 
            src/barrel.cpp
            src/matrix.cpp
            src/MyString.cpp
            src/rect.cpp
            src/textwrapper.cpp
) # объединяем всю функциональность в библиотеку
target_include_directories(lab1_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(lab1 src/lab1.cpp) #cmake сам генерирует правильную сборку, поэтому происходит перекомпиляцию только тех файлов, которые изменили
target_link_libraries(lab1 lab1_library)

enable_testing()
add_subdirectory(tests)# подключаем cmake в папке tests