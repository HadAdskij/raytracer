PROJECT(RaytracerDebugger)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if(WIN32)
	set(WIN_GLUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GL")
endif()

ADD_SUBDIRECTORY(src)
