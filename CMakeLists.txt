cmake_minimum_required(VERSION 3.8)
project(Winter)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp" "Source/*.c")
file(GLOB_RECURSE HEADER_FILES "Include/*.h")

add_executable(Winter ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(Winter PUBLIC "Include")

# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

message(STATUS "GLFW3_INCLUDE_DIR: ${GLFW3_INCLUDE_DIR}")
message(STATUS "GLM_INCLUDE_DIRS: ${GLM_INCLUDE_DIRS}")
target_include_directories(Winter PRIVATE ${GLFW3_INCLUDE_DIR} ${GLM_INCLUDE_DIRS})
target_link_libraries(Winter GLFW::glfw3)