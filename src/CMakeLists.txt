file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true include/*.cpp)
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true include/*.h)

set(INCLUDE_SRC ${SOURCES} ${HEADERS})

# Configure assets header file
configure_file(ProjectDir.h.in ProjectDir.h)

add_subdirectory(GL1_BasicPoint)
add_subdirectory(GL2_AllShaders)