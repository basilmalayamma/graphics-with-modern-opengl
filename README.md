Section 2: Introduction to GLEW, GLFW and SDL
---------------------------------------------

* GLEW: OpenGL Extension Wrangler. 
	* Built in opengl libraries in our system only alows to interface with opengl version 1.1.
	* GLEW is used to interface with opengl libraries with version above 1.1.
	* Load OpenGL Extension. GLEW can check whether an extension exist for a platform.
	* summary: lib to interface with modern opengl and handle platform specific extensions safely.

* GLFW: OpenGL Framework.
	* Handles window creation and control.
	* Pick up input from keyboard, mouse etc and process them.
	* Allows multiple monitor support.
	* Interaction with the window is done through the context.
	* summary: lib to create windows and context and handle user input / lib to create a window using opengl context.

* SDL: Simple DirectMedia Layer
	* GLFW + some additional features(Audio, threading, filesystem etc).
	* Heavy weight.

GLUT is no longer maintaned, try to avoid it.
=============================================================================================================================

Section 3: Coding.
=============================================================================================================================

Section 4: Shaders and the rendering pipeline.
---------------------------------------------

* Rendering pipeline: series of stage that take place inorder to render an image to the screen.
* Among this 4 stages are programmable via shaders(vertex shader, fragment shader, geometric shader, tessellation shader).
* There is also one more shader compute shader, this is not part of rendering pipeline. It works seperately.
* Shaders are written in GLSL(OpenGL Shading Language).
* Pipeline stages:
	1. Vertex Specification:
		* vertex: a point defined by (x,y,z)
		* primitive: simple shape defined by one or more vetrices(points, line, triangles).
		* vertex specidication: setting up of the data of the vertices for the primitives we want to render.
		* 3 main parts: VAO's, VBO's and attrib pointers.
			1. VAO: defines what data a vertex has like position, colour, texture etc.
			2. VBO: defines the data itself.
			3. Attribe pointers: where and how the shaders can access data.
		* glDrawAyyars() will draw based on the last bounded VAO
	2. Vertex Shader:
		* Handles vertices individually. i.e we can modify individual vertices if we want.
		* Application invlove multiplying with translation matrix, rotational matrix, projection matrix, putting offset etc.
		* Not optional.
		* Must define gl_Position
		* Can define additional output that can be picked by other shaders.
		* Input will be vetex it self.
		* Must define version in shader.
	3. Tessellation:
		* Divide up the data to smaller primitives.
		* Eg: quadrilateral -> triangle.
	4. Geometric Shader:
		* Handles primitives(Group of vertices).
		* Take prmitives and emits their vertices.
	5. Vertex Post processing:
		* It has 2 parts:
			1. Transform f/b:
				* Result of vertex and geometric shader are stored to buffers for later use.	
			2. Clipping:
				* Primitives that are out of visible area are removed. 
				* Positions are converted from clip space to window space.
	6. Primitive assembly:
		* Converting vertices in to series of primitives. Eg: 6 vertices -> 2 triangles.
		* Face culling: Removing the faces of objects that we can not see(i.e surfaces facing away from the viewer).
	7. Rasterization:
		* Primitives -> Fragments.
		* Fragments are not actually the pixels, they are the peices of data for each pixels. 
	8. Fragment Shader.
		* Handles data for each fragment.
		* The output will be the colour for each pixels that the fragment covers.
	9. Per sample operation:
		* Series of tests are done to determine whether the fragment should be drawn.
		* Important test: Depth test.
		* Colour belnding: used to produce transparency.
		* The output will be written to currently bound framebuffer.
		* In double buffering the o/p is written to the back buffer and using glSwapbuffers this is brought to front.
=============================================================================================================================

Section 5: Coding.
=============================================================================================================================

Section 6: Vectors, metrices and uniform variables.
----------------------------------------------------

* Vector:
	* Quatity with magnitude and direction.
	* Used to represent har far an object and in what direction.
	* x-y plane is the screen and z will be coming in or out of plane.
	* Operations:
		1. Addition / subtraction: role in OpenGL?
		2. Multiplication.
		3. Dot Product.
		4. Cross Product
	* vec4 = vector with 4 values.

* Matrix:
	* Used for handling model transforms, projections and views.
	* Model transforms: Moving objects in the scene (translations, rotation and scaling)
	* Projections: How things are viewed
	* View: Position of camera.
	* Matrix transforms:
		1. Translation: Used for changing positions of a vector. Change the 4th coloumn of identity matrix.
		2. Scaling: Used to resize a vector. Change the diagonal elemets of an identity matrix.
		3. Rotation: Advanced, little complicated.
	* mat4 = 4x4 matrix.

* GLM(OpenGL Mathematics) Library will take care of all this in OpenGL.

* If we want Translation and scaling, then just multiply 2 metrixes and use it as a single matrix.
* translation-matrix * scaling-matrix = combined-matrix. In this case scaling will happen first and then translation. So the scaled matrix will be translated(and vice versa). Oreder matters, last operation happens first.

* Uniform variables:
	* Variables used by the shader.
	* They are global to the shader. Where as normal variables in shader will be run for each vertices.
