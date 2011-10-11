cmake_minimum_required(VERSION 2.6)

#set the name of the project
SET(PROJECTNAME LSys)


#Déclaration du projet
project(${PROJECTNAME})

#Repertoire de sortie des compilations
#set(LIBRARY_OUTPUT_PATH ../bin)


#inclusion d'OSG et OpenThreads
FIND_PACKAGE(OpenSceneGraph 2.8.0 REQUIRED QUIET COMPONENTS osg osgDB osgUtil osgGA osgText osgFX osgViewer)


#ajout des includes des libs dans les paths d'include
include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

#Do not forget its own includes
include_directories("src")

#add bin include dir
set( OSGBuildRootDirectory "Please specify osg binaries directory where Cmake puts the project file" CACHE PATH "OSG Root directory")
include_directories("${OSGBuildRootDirectory}/include")



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
add_executable(
	${PROJECTNAME}
	${cpp_source_files} ${header_source_files}
)

#ajout des libs au linker
target_link_libraries(
	${PROJECTNAME}
	${OPENSCENEGRAPH_LIBRARIES}
)


