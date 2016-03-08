
Readme

Building
	Its a good idea to make clean before running make
	The executable it outputs is ./island

Source
	Headerfiles and source are not cleanly separated which is why its a good idea to make clean.
	Throughout all source code I use a Point struct the same as if it were also a 3D vector so
		view parameter caluculations are done with Point. 

Controls
	wads:
		w: move forward, hold it to speed up.
		s: move backward, hold it to speed up.
		a: roll camera left
		d: roll camera right

	space: stop all motion

	mouse:
		horizontal: yaws the camera
		vertical: pitches the camera
		circular: avoid this! 
			For some reason it rolls slightly in addition to panning the view

Animation:
	The boat is animated to swim in a circle around the lighthouse and bob up and down
	The lighthouse sways back and forth as if it were floating

Object models:
	Everything in the scene has its own object model which can be found in the object folder.
	Texture bitmaps can also be found here.
	The lighthouse base has its normals specified in the object. Everything else has automatically calculated normals.
	Many objects have texture coordinates in the object. Even though I just mapped quads from 0,0 to 1,1 
		it is set up to handle more general texture mappings.
	Objects are read in and processed using gl_polygon for each face regardless of shape. Normal and texture info 
		is stored in point arrays and not processed until the faces are fully constructed.

Lighting, shading, rendering, effects
	Ill admit I was floundering quite a bit on this section. Code for all lighting and materials is there, effective or not.
	I spent a great deal of time adjusting the parameters to see how things change but never got satisfactory results.
	The best I got out of this section was different colors and some shininess. I tried adding animation to the spotlight
	so that it would be easier to locate it and observe its effects... never once to be seen. At least I was able to see
	how ambient light changes the brightness and diffuse heavily impacts color. Specified vertex normals yielded only minor changes.
	I was expecting to see a rounded object because I specifically modified them to be different from the actual polygons face normals.

