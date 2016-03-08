Readme File
Created by Nick Barnes
Csce 441-500, Keyser

Files:
	global.h 	main.cpp 	point.h 	point.cpp 	shape.h 	shape.cpp 	tracer.h 	tracer.cpp 

	Header files are just interfaces.
	main.cpp sets up the scene and tells the ray tracer to do its work.
	point.cpp provides utilities for points, vectors, and rays.
	shape.cpp provides geometry for spheres, planes, and intersections with rays. 
	tracer.cpp provides the brains for tracing the scene.

Scene settings:
	All settings are found in the init function towards the bottom of main.cpp

Lighting:
	The ambient light is white. There are 3 point lights that are red, white, and blue.

Materials:
	The ambient components are the same color as the diffuse components just much dimmer.
	The planes have 0 ambiance so that they appear to completely disappear into the distance
		without a hard edge at the transition point where the view turns parallel.
	The red sphere has blue shininess.
	The white sphere has green shininess.
	All other spheres have white shininess.

Reflection:
	There are 3 objects with varying reflectivity. The green sphere has 20%, the pink plane has 50%, and the gray sphere has 70%.

