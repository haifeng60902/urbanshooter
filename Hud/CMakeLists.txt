cmake_minimum_required(VERSION 2.6)

#set the name of the project
SET(LIBRARYNAME Hud)


#Déclaration du projet
project(${LIBRARYNAME})

#Repertoire de sortie des compilations
set(LIBRARY_OUTPUT_PATH lib)
#SET_TARGET_PROPERTIES(${LIBRARYNAME} LIBRARY_OUTPUT_DIRECTORY lib)

#link flags
#SET_TARGET_PROPERTIES(${LIBRARYNAME} PROPERTIES LINK_FLAGS "DEBUG")
#SET_TARGET_PROPERTIES(${LIBRARYNAME} PROPERTIES LINK_FLAGS "RELEASE")

#inclusion d'OSG

FIND_PACKAGE(OpenThreads)
FIND_PACKAGE(OpenSceneGraph 2.8.0 REQUIRED QUIET COMPONENTS osg osgDB osgUtil osgGA osgText osgFX osgViewer)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
include_directories(${OPENTHREADS_INCLUDE_DIRS})

#Do not forget its own includes
include_directories("./src")



#Génération de la liste des fichiers header
file(
	GLOB_RECURSE
	header_source_files
	src/*.h
)
#Génération de la liste des fichiers cpp
file(
	GLOB_RECURSE
	cpp_source_files
	src/*.cpp
)


#Déclaration de la lib
add_library(
	${LIBRARYNAME}
	SHARED
	${cpp_source_files} ${header_source_files}
)

#ajout au linker
target_link_libraries(
	${LIBRARYNAME}
	${OPENTHREADS_LIBRARIES}
	${OPENSCENEGRAPH_LIBRARIES}
)
