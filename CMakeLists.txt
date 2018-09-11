cmake_minimum_required(VERSION 3.8)
project(Winter)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp" "Source/*.c")
file(GLOB_RECURSE HEADER_FILES "Include/*.h")
add_executable(Winter ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(Winter PUBLIC "Include")
target_link_libraries(Winter GL GLEW glfw)