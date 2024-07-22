cmake_minimum_required (VERSION 3.8)
project ("detect-circle" VERSION 1.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
endif(MSVC)
find_package(OpenCV CONFIG REQUIRED)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(MIL_LIB
)
SET(TARGET_H
    util.h
)
SET(TARGET_SRC
    circleDetection.cpp
    util.cpp
    #circle_param_check.cpp
)
# Add source to this project's executable.
add_executable(${PROJECT_NAME}  ${TARGET_SRC} ${TARGET_H})
target_link_directories(${PROJECT_NAME} PRIVATE $ENV{MIL_Path}/../Lib)
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS} 
    ${MIL_LIB})
target_include_directories(${PROJECT_NAME} PRIVATE 
    $ENV{MIL_Path}/../Include
)

# Add custom command to copy Image folder
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Image
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Image
)

# Add custom target to ensure the copy command is always executed
add_custom_target(copy_image_folder ALL DEPENDS ${PROJECT_NAME})