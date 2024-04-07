cmake_minimum_required(VERSION 3.0.0)
project(ModalSolver)

add_subdirectory(include)
add_subdirectory(Dependencies)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/ThirdParty/eigen-3.4.0)

set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/Modal.cpp)

target_link_libraries(${PROJECT_NAME}
   PUBLIC
   ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/glfw3.lib
   ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/glew32.lib
   ${CMAKE_SOURCE_DIR}/Dependencies/GLEW/glew32s.lib
   opengl32.lib
   glu32.lib
   core)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_if_different
       "${CMAKE_SOURCE_DIR}/Dependencies/GLEW/glew32.dll"
       $<TARGET_FILE_DIR:${PROJECT_NAME}>)

