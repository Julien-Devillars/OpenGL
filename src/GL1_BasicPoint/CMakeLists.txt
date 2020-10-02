set(SUB_PROJECT_NAME GL1_BasicPoint)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.cpp)
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true *.h)
file(GLOB_RECURSE SHADERS LIST_DIRECTORIES true shaders/*)

add_compile_definitions(PROJECT_NAME $(ProjectName))


add_executable(${SUB_PROJECT_NAME} 
			${SOURCES} 
			${HEADERS} 
			${INCLUDE_SRC} 
			${SHADERS}
			)

source_group("Shaders" FILES ${SHADERS})

target_link_libraries(${SUB_PROJECT_NAME} PUBLIC ${LIBS})