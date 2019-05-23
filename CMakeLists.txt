########################################################
# cmake file for building Marlin
# @author Jan Engels, Desy IT
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
########################################################

# project name
PROJECT( slcio2txt )


# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 1 )
SET( ${PROJECT_NAME}_VERSION_MINOR 0 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )



### DEPENDENCIES ############################################################

FIND_PACKAGE( ILCUTIL COMPONENTS ILCSOFT_CMAKE_MODULES streamlog ILCTEST REQUIRED )
#FIND_PACKAGE( ILCSOFT_CMAKE_MODULES 1.11 REQUIRED )

# load default settings from ILCSOFT_CMAKE_MODULES
INCLUDE( ilcsoft_default_settings )


# required packages
FIND_PACKAGE( LCIO REQUIRED )
INCLUDE_DIRECTORIES( SYSTEM ${LCIO_INCLUDE_DIRS} )

ADD_EXECUTABLE( slcio2txt slcio2txt.cc )
TARGET_LINK_LIBRARIES( slcio2txt ${LCIO_LIBRARIES} )
INSTALL( TARGETS slcio2txt DESTINATION bin )

# display some variables and write them to cache
DISPLAY_STD_VARIABLES()
