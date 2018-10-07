#
# Defines:
# - Imported target: GLFW::glfw3
# - GLFW3_LIBRARY
# - GLFW3_INCLUDE_DIR
#
set(GLFW3_ROOT "${GLFW3_ROOT}" CACHE PATH "Root directory of GLFW3")
find_library(GLFW3_LIBRARY NAMES glfw3 glfw HINTS "${GLFW3_ROOT}/lib")
find_path(GLFW3_INCLUDE_DIR NAMES "GLFW/glfw3.h" HINTS "${GLFW3_ROOT}/include")
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    glfw3
    DEFAULT_MSG
    GLFW3_LIBRARY
    GLFW3_INCLUDE_DIR
)

if (GLFW3_FOUND)
    mark_as_advanced(GLFW3_ROOT)
    add_library(GLFW::glfw3 STATIC IMPORTED)
    set_target_properties(
        GLFW::glfw3 PROPERTIES
        IMPORTED_LOCATION ${GLFW3_LIBRARY})
endif()

mark_as_advanced(GLFW3_LIBRARY GLFW3_INCLUDE_DIR)