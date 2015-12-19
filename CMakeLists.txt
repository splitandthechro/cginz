cmake_minimum_required (VERSION 2.8)

# Project
project (cginz)

# Find OpenGL
message (STATUS " Searching for OpenGL")
find_package (OPENGL REQUIRED)
if (NOT OPENGL_FOUND)
    message (FATAL_ERROR " OpenGL not found!")
elseif (OPENGL_FOUND)
    include_directories (${OPENGL_INCLUDE_DIRS})
    link_directories (${OPENGL_LIBRARY_DIRS})
    add_definitions (${OPENGL_DEFINITIONS})
endif (NOT OPENGL_FOUND)

# Find GLEW
message (STATUS " Searching for GLEW")
find_package (GLEW REQUIRED)
if (NOT GLEW_FOUND)
    message (FATAL_ERROR " GLEW not found!")
elseif (GLEW_FOUND)
    include_directories (${GLEW_INCLUDE_DIRS})
    link_directories (${GLEW_LIBRARY_DIRS})
    add_definitions (${GLEW_DEFINITIONS})
endif (NOT GLEW_FOUND)

# Find GLUT
message (STATUS " Searching for GLUT")
find_package (GLUT REQUIRED)
if (NOT GLUT_FOUND)
    message (FATAL_ERROR " GLUT not found!")
elseif (GLUT_FOUND)
    include_directories (${GLUT_INCLUDE_DIRS})
    link_directories (${GLUT_LIBRARY_DIRS})
    add_definitions (${GLUT_DEFINITIONS})
endif (NOT GLUT_FOUND)

# Find pthread
set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)
if (NOT THREADS_FOUND)
    message (FATAL_ERROR " THREADS not found!")
elseif (THREADS_FOUND)
    include_directories (${THREADS_INCLUDE_DIRS})
    link_directories (${THREADS_LIBRARY_DIRS})
    add_definitions (${THREADS_DEFINITIONS})
endif (NOT THREADS_FOUND)

# Include files
aux_source_directory (. SRC_LIST)
add_executable (${PROJECT_NAME}_test ${SRC_LIST})
add_library (${PROJECT_NAME} SHARED ${SRC_LIST})

# Link
set (
    LINK_ALL
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLUT_LIBRARY}
    pthread
)
target_link_libraries (${PROJECT_NAME}_test ${LINK_ALL})
target_link_libraries (${PROJECT_NAME} ${LINK_ALL})
