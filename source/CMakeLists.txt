# file CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

project(Abssal-Engine)

option(USE_PRECOMPILED_HEADERS			"Use precompiled headers to speedup buld" ON)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
######################	LIBRARYES ######################
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

#include OpenGL for rendering
find_package(OPENGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#handler for OpenGL Functions
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

#search for sdl for low level interface 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#font rendering
find_package(SDL2ttf REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIR})

#
find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIR})


include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/contrib/glm/include)
include_directories(${CMAKE_SOURCE_DIR}/contrib/png/include)
include_directories(${CMAKE_SOURCE_DIR}/contrib/tinyxml2/include)


######################	SOURCE ######################
file(GLOB ENGINE_INCLUDES *.h)
file(GLOB ENGINE_SOURCES *.cpp)
source_group("" FILES ${ENGINE_INCLUDES})
source_group("" FILES ${ENGINE_SOURCES})

file(GLOB SYS_INCLUDES sys/*.h)
file(GLOB SYS_SOURCES sys/*.cpp)
source_group("sys" FILES ${SYS_INCLUDES})
source_group("sys" FILES ${SYS_SOURCES})

file(GLOB SYS_FILESYSTEM_INCLUDES sys/fileSystem/*.h)
file(GLOB SYS_FILESYSTEM_SOURCES sys/fileSystem/*.cpp)
source_group("sys\\fileSystem" FILES ${SYS_FILESYSTEM_INCLUDES})
source_group("sys\\fileSystem" FILES ${SYS_FILESYSTEM_SOURCES})

file(GLOB SYS_INPUTHANDLER_INCLUDES sys/inputHandler/*.h)
file(GLOB SYS_INPUTHANDLER_SOURCES sys/inputHandler/*.cpp)
source_group("sys\\inputHandler" FILES ${SYS_INPUTHANDLER_INCLUDES})
source_group("sys\\inputHandler" FILES ${SYS_INPUTHANDLER_SOURCES})

file(GLOB SYS_MEMORY_INCLUDES sys/memory/*.h)
file(GLOB SYS_MEMORY_SOURCES sys/memory/*.cpp)
source_group("sys\\memory" FILES ${SYS_MEMORY_INCLUDES})
source_group("sys\\memory" FILES ${SYS_MEMORY_SOURCES})

file(GLOB SYS_RESOURCES_INCLUDES sys/resources/*.h)
file(GLOB SYS_RESOURCES_SOURCES sys/resources/*.cpp)
source_group("sys\\resources" FILES ${SYS_RESOURCES_INCLUDES})
source_group("sys\\resources" FILES ${SYS_RESOURCES_SOURCES})

file(GLOB SYS_THREADING_INCLUDES sys/threading/*.h)
file(GLOB SYS_THREADING_SOURCES sys/threading/*.cpp)
source_group("sys\\threading" FILES ${SYS_THREADING_INCLUDES})
source_group("sys\\threading" FILES ${SYS_THREADING_SOURCES})

file(GLOB FRAMEWORK_INCLUDES framework/*.h)
file(GLOB FRAMEWORK_SOURCES framework/*.cpp)
source_group("framework" FILES ${FRAMEWORK_INCLUDES})
source_group("framework" FILES ${FRAMEWORK_SOURCES})

file(GLOB GAMELOGIC_INCLUDES gameLogic/*.h)
file(GLOB GAMELOGIC_SOURCES gameLogic/*.cpp)
source_group("gameLogic" FILES ${GAMELOGIC_INCLUDES})
source_group("gameLogic" FILES ${GAMELOGIC_SOURCES})

file(GLOB RENDER_INCLUDES render/*.h)
file(GLOB RENDER_SOURCES render/*.cpp)
source_group("render" FILES ${RENDER_INCLUDES})
source_group("render" FILES ${RENDER_SOURCES})

file(GLOB RENDER_GUI_INCLUDES render/gui/*.h)
file(GLOB RENDER_GUI_SOURCES render/gui/*.cpp)
source_group("render\\gui" FILES ${RENDER_GUI_INCLUDES})
source_group("render\\gui" FILES ${RENDER_GUI_SOURCES})

file(GLOB RENDER_IMAGE_INCLUDES render/image/*.h)
file(GLOB RENDER_IMAGE_SOURCES render/image/*.cpp)
source_group("render\\image" FILES ${RENDER_IMAGE_INCLUDES})
source_group("render\\image" FILES ${RENDER_IMAGE_SOURCES})

file(GLOB RENDER_TEXT_INCLUDES render/text/*.h)
file(GLOB RENDER_TEXT_SOURCES render/text/*.cpp)
source_group("render\\text" FILES ${RENDER_TEXT_INCLUDES})
source_group("render\\text" FILES ${RENDER_TEXT_SOURCES})

set( ENGINE_INCLUDES_ALL 
	${ENGINE_INCLUDES}
	${SYS_INCLUDES}
	${SYS_FILESYSTEM_INCLUDES}
	${SYS_INPUTHANDLER_INCLUDES}
	${SYS_MEMORY_INCLUDES}
	${SYS_RESOURCES_INCLUDES}
	${SYS_THREADING_INCLUDES}
	${FRAMEWORK_INCLUDES}
	${GAMELOGIC_INCLUDES}
	${RENDER_INCLUDES}
	${RENDER_GUI_INCLUDES}
	${RENDER_IMAGE_INCLUDES}
	${RENDER_TEXT_INCLUDES}
	${CONTRIB_INCLUDES}
	)

set( ENGINE_SOURCES_ALL 
	${ENGINE_SOURCES}
	${SYS_SOURCES}
	${SYS_FILESYSTEM_SOURCES}
	${SYS_INPUTHANDLER_SOURCES}
	${SYS_MEMORY_SOURCES}
	${SYS_RESOURCES_SOURCES}
	${SYS_THREADING_SOURCES}
	${FRAMEWORK_SOURCES}
	${GAMELOGIC_SOURCES}
	${RENDER_SOURCES}
	${RENDER_SOURCES}
	${RENDER_GUI_SOURCES}
	${RENDER_IMAGE_SOURCES}
	${RENDER_TEXT_SOURCES}
	${CONTRIB_SOURCES}
	)

set(INCLUDE_LIBS
	${GLEW_LIBS}
	${SDL2TTF_LIBRARIES}
	${SDL2_LIBRARIES}
	${OPENGL_LIBRARY}
	${GLEW_LIBRARY}
	${SDL2_LIBRARY}
	)

######################	Contrib Lib ######################
file(GLOB CONTRIB_TINYXML2_INCLUDES contrib/tinyxml2/include/*.h)
file(GLOB CONTRIB_TINYXML2_SOURCES contrib/tinyxml2/src/*.cpp)
source_group("contrib\\tinyxml2" FILES ${CONTRIB_TINYXML2_INCLUDES})
source_group("contrib\\tinyxml2" FILES ${CONTRIB_TINYXML2_SOURCES})
list(APPEND ENGINE_INCLUDES_ALL  ${CONTRIB_TINYXML2_INCLUDES})
list(APPEND ENGINE_SOURCES_ALL ${CONTRIB_TINYXML2_SOURCES})

#file(GLOB CONTRIB_PNG_INCLUDES contrib/png/include/*.h)
#file(GLOB CONTRIB_PNG_SOURCES contrib/png/src/*.c)
#source_group("contrib\\png" FILES ${CONTRIB_PNG_INCLUDES})
#source_group("contrib\\png" FILES ${CONTRIB_PNG_SOURCES})
#list(APPEND ENGINE_INCLUDES_ALL CONTRIB_PNG_INCLUDES)
#list(APPEND ENGINE_SOURCES_ALL CONTRIB_PNG_SOURCES)

if(USE_PRECOMPILED_HEADERS)
	set(ABSSAL_PRECOMPILED_SOURCES ${ENGINE_SOURCES_ALL})
	#remove sources that not include the precompiled header 
	list(REMOVE_ITEM ABSSAL_PRECOMPILED_SOURCES ${CONTRIB_TINYXML2_SOURCES})
#	list(REMOVE_ITEM ABSSAL_PRECOMPILED_SOURCES ${CONTRIB_PNG_SOURCES})
	list(REMOVE_ITEM ABSSAL_PRECOMPILED_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/precompiled.cpp)
	
if(MSVC)
	   		set_source_files_properties( ${ABSSAL_PRECOMPILED_SOURCES} PROPERTIES
									COMPILE_FLAGS "/Yuprecompiled.h"
									OBJECT_DEPENDS "precompiled.pch"
		)
		
		set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/precompiled.cpp PROPERTIES
									COMPILE_FLAGS "/Ycprecompiled.h"
									OBJECT_OUTPUTS "precompiled.pch"
		)
	else()
		foreach( src_file ${ABSSAL_PRECOMPILED_SOURCES} )
		#message(STATUS "-include precompiled.h for ${src_file}")
		set_source_files_properties(
			${src_file}
			PROPERTIES
			COMPILE_FLAGS "-include ${CMAKE_CURRENT_SOURCE_DIR}/precompiled.h"
			)
		endforeach()
		
		# precompiled magic for GCC/clang, adapted from https://gist.github.com/573926
		STRING(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" _flags_var_name)
		SET(_compiler_FLAGS ${${_flags_var_name}})
		GET_DIRECTORY_PROPERTY(_directory_flags INCLUDE_DIRECTORIES)
		FOREACH(item ${_directory_flags})
		LIST(APPEND _compiler_FLAGS " -I${item}")
		ENDFOREACH(item)
		
		add_custom_target(precomp_header_engine ALL
	                  COMMAND ${CMAKE_CXX_COMPILER} ${_compiler_FLAGS} -x c++-header precompiled.h -o precompiled.h.gch
	                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	                  COMMENT "Creating Engine/precompiled.h.gch for engine"
	                  )
	endif()
endif(USE_PRECOMPILED_HEADERS)

add_executable(Abssal-Engine-Demo ${ENGINE_SOURCES_ALL} ${ENGINE_INCLUDES_ALL})
target_link_libraries(Abssal-Engine-Demo ${INCLUDE_LIBS})

#if (USE_PRECOMPILED_HEADERS)
	# make sure precompiled header is created before executable is compiled
#	add_dependencies(Abssal-Engine-Demo precomp_header_engine)
#endif(USE_PRECOMPILED_HEADERS)	
