# Тест 1
add_executable(test_bounding_rect test_bounding_rect.cpp)
target_link_libraries(test_bounding_rect lab1_library) #линкуем тестовую прогграмму с библиотекой
target_include_directories(test_bounding_rect PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Тест 2
add_executable(test_rect_basic_methods test_rect_basic_methods.cpp)
target_link_libraries(test_rect_basic_methods lab1_library)
target_include_directories(test_rect_basic_methods PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Тест 3
add_executable(test_rect_operations test_rect_operations.cpp)
target_link_libraries(test_rect_operations lab1_library)
target_include_directories(test_rect_operations PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Тест 4
add_executable(test_rect_properties test_rect_properties.cpp)
target_link_libraries(test_rect_properties lab1_library)
target_include_directories(test_rect_properties PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_test(NAME test_bounding_rect COMMAND test_bounding_rect)
add_test(NAME test_rect_basic_methods COMMAND test_rect_basic_methods)
add_test(NAME test_rect_operations COMMAND test_rect_operations)
add_test(NAME test_rect_properties COMMAND test_rect_properties)