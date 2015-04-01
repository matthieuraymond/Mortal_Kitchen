cmake_minimum_required(VERSION 2.6)
project(common)

IF(WIN32)
ADD_DEFINITIONS(-DDATA_PATH=\"${CMAKE_SOURCE_DIR}\")
ELSE(WIN32)
ADD_DEFINITIONS(-DDATA_PATH=\\"${CMAKE_SOURCE_DIR}\\")
ENDIF(WIN32)

SET(COMMON
    base.cpp
	drawimage.cpp
	drawimage.h
	drawimage_sh.fp
	drawimage_sh.vp
	drawimage_sh.h
)

SET(SHADERS
	drawimage_sh
)

ADD_LIBRARY(common ${COMMON})

AUTO_BIND_SHADERS( ${SHADERS} )
