cmake_minimum_required(VERSION 3.8)
project(Winter)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE WINTER_SOURCE_FILES "Source/*.cpp" "Source/*.c")
file(GLOB_RECURSE WINTER_HEADER_FILES "Include/*.h")

add_executable(Winter ${WINTER_SOURCE_FILES} ${WINTER_HEADER_FILES})
target_include_directories(Winter PUBLIC "Include")

# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules")
find_package(glfw3 REQUIRED)
find_package(glm CONFIG REQUIRED)

target_include_directories(Winter PRIVATE ${GLFW3_INCLUDE_DIR})
target_link_libraries(Winter GLFW::glfw3 glm)