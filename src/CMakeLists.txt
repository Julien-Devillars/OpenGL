file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true include/*.cpp)
file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true include/*.h)

set(INCLUDE_SRC ${SOURCES} ${HEADERS})

# Configure assets header file
configure_file(ProjectDir.h.in ProjectDir.h)

FILE(GLOB SUBDIRS LIST_DIRECTORIES true "GL*")

MESSAGE(STATUS "PROJECTS : ")

FOREACH(DIRS ${SUBDIRS})
	get_filename_component(DIRNAME ${DIRS} NAME [CACHE])
	
	MESSAGE(STATUS "Found " ${DIRNAME})
	
	set(SUB_PROJECT_NAME ${DIRNAME})
	
	file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true ${DIRS}/*.cpp)
	file(GLOB_RECURSE HEADERS LIST_DIRECTORIES true ${DIRS}/*.h)
	file(GLOB_RECURSE SHADERS LIST_DIRECTORIES true ${DIRS}/shaders/*)
	

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
ENDFOREACH()