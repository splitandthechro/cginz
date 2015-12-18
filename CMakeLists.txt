cmake_minimum_required (VERSION 2.8)

# Project
project (cginz)

# Find GLUT
find_package (GLUT REQUIRED)
include_directories (${GLUT_INCLUDE_DIRS})
link_directories (${GLUT_LIBRARY_DIRS})
add_definitions (${GLUT_DEFINITIONS})
if (NOT GLUT_FOUND)
    message (ERROR " GLUT not found!")
endif (NOT GLUT_FOUND)

# Find OpenGL
find_package (OpenGL REQUIRED)
include_directories (${OPENGL_INCLUDE_DIRS})
link_directories (${OPENGL_LIBRARY_DIRS})
add_definitions (${OPENGL_DEFINITIONS})
if (NOT OPENGL_FOUND)
    message (ERROR " OpenGL not found!")
endif (NOT OPENGL_FOUND)

# Find pthread
set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)


# Include files
aux_source_directory (. SRC_LIST)
add_executable (${PROJECT_NAME}_test ${SRC_LIST})
add_library (${PROJECT_NAME} SHARED ${SRC_LIST})

# Link
target_link_libraries (${PROJECT_NAME}_test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries (${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Link pthread
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)
target_link_libraries (${PROJECT_NAME}_test pthread)
target_link_libraries (${PROJECT_NAME} pthread)
