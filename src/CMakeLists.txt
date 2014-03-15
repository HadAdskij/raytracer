FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=gnu++0x)
endif()

ADD_EXECUTABLE(raytracer_test test.cpp
	Color.h
	Cylinder.cpp Cylinder.h
	Sphere.cpp Sphere.h
	Plane.cpp Plane.h
	Ray.h
	Surface.h
	Vector3.h Vector3.cpp
	View.cpp View.h
	Light.h)

TARGET_LINK_LIBRARIES(raytracer_test GL GLU glut pthread)
