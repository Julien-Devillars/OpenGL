set(SUB_PROJECT_NAME GL4_Textures)

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
source_group("Include Files" FILES ${INCLUDE_SRC})

target_link_libraries(${SUB_PROJECT_NAME} PUBLIC ${LIBS})

add_custom_command(TARGET ${SUB_PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/dlls"
		$<TARGET_FILE_DIR:${SUB_PROJECT_NAME}>)