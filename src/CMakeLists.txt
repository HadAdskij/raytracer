# We use our own GLUT in windows
if(!WIN32)
	FIND_PACKAGE(GLUT REQUIRED)
else()
	include_directories(${WIN_GLUT_DIR})
	link_directories(${WIN_GLUT_DIR})
endif()
FIND_PACKAGE(OpenGL REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=gnu++0x)
endif()

ADD_EXECUTABLE(raytracer test.cpp
	Color.h
	Cylinder.cpp Cylinder.h
	Sphere.cpp Sphere.h
	Plane.cpp Plane.h
	Ray.h
	Surface.h
	Vector3.h Vector3.cpp
	View.cpp View.h
	Light.h)

if(!WIN32)
	list(APPEND LIBRARIES GL GLU glut pthread)
else()
	list(APPEND LIBRARIES glut32)
endif()

if(WIN32)
	add_custom_command(TARGET raytracer POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${WIN_GLUT_DIR}/glut32.dll"
		$<TARGET_FILE_DIR:raytracer>)
endif()

TARGET_LINK_LIBRARIES(raytracer ${LIBRARIES})
