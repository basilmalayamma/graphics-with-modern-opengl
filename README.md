Introduction to GLEW, GLFW and SDL
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

Shaders and the rendering pipeline.
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

Vectors, metrices and uniform variables.
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
=============================================================================================================================

Interpolation, Indexed Draws and projections.
--------------------------------------------------------

* Interpolation:
	* Vertex shader deals only with the vertices, the values in between the vertices are calculated using interpolation.
	* It happens in rasterization stage.
	* The weighted average of 3 vertices on a triangle is passed on.
	
* Indexed Draws:
	* Until now we are passing the vertices as such.
	* When the number of shapes to draw increases passing defining each vertices becomes messy.
	* Also same points should be defined multiple times.
	* So we use arrays and use index to obtain the vertices.
	* Need of defining same points multiple times can be eliminted.
	* We can reference same points multiple times so it should be defined only once. 

* Projections:
	* Describes how we see the things.
	* Used to convert view space -> clip space.
	* Used to give a 3d look.
	* Coordinate system:
		* Local space: (Coordinates with out any transformations)Raw position of each vertex from origin. 
		* World space: Coordinates obtained by applying transformations to local space.
		* View spcce: Coordinares w.r.t camera view. Obtained by mutiplying with projection matrix.
		* Clip space: View space coordinates in the area not to be clipped.
		* Screen space: Clip space coordinates coverted to coordinates of window.
	* We need to define an area of frustum, i.e area not to be clipped.
	* 2 types:
		* Orthographics:
			* Used for 2D applications.
			* Frustum will be a cuboid.
			* There will not be any depth effect. i.e moving object close and far will not change the size.
		* Perspective :
			* Used for 3D applications.
			* Frustum will be a truncated pyramid.
			* Gives an illusion of depth. i.e pixel on near plane diverges at an angle to reach matching point in far plane.
	* Generate a matrix using glm and bind it to a uniform in the shader.
	* "gl_Position = projection * view * model * vec4(pos, 1)" order is important(treated from right to left i.e: vector -> world space -> view space -> clip space).
	
=============================================================================================================================

The Camera and user input
-------------------------

* Camera process the scene as seen from the view space.
* View space is the coordinate system with each vertex as seen from the camera.
* View matrix is used to convert coordinates from world space to view space.
* View matrix composed of 4 values:
	1. Position of camera.
	2. Direction of camera: it actually points to the opposite direction of intuitive direction.
	3. Right: Vectore facing right of the camera. Cross product of up vector and direction vector.
	4. Up: Vector facing left of camera. Cross product of direction vector and right vector. 

* Delta time: 
	* Amount of time passed since last loop.
	* This is used to keep the movement of objects at a slower speed and at consistent speed.
	* deltaTime = currentTime - lastTime
	* Multiply cameras movement speed with delta time.
	* Used for synchronizing movement of all objects in the frame.
	* Link: 

* Turning:
	* 3 types of movement:
		1. Pitch: up and down
		2. Yaw: left and right
		3. Roll: rolling

* Implementation:
	* Set the cursor callback.
	* Store old mouse postion and compare with the new mouse position.
	* Use this difference to determine pitch/yaw change.

=============================================================================================================================

Textures and Image loadings
---------------------------

* Textures:
	* Images used to add extra details to an object.
	* Points in texture are called texels not pixels.
	* Texels will have values btw 0 and 1.
	* Normally we will define a texture and then map the texels to the vertices.

* MipMaps:
	* Resolution limits for textures.
	* Problem:
		* when we move close to the object it becomes more pixelated.
		* when we move far it attempts to draw multiple texels of on one pixel.
	* Solution: Mipmaps, create multiple verions of texture at different resolutions and switch btw them based on distance.

* Filters:
	* Used while rendering off centre texels.
	* 2 possibilities:
		1. Nearest: texel with more ovrelap is drawn.
		2. Linear: it takes Wighted average of all texels sourrounding it.
	* MIN_FILTER: filter to be applied when texture is made smaller.
	* MAG_FILTER: filter to be applied when texture is made larger.

* Wrap:
	* Texels will be usually in range of 0 to 1. What if value exceed?
	* To handle this case we use wrap parameter.
	* There are 4 ways to handle it:
		1. Repeat the texture.
		2. Repeat mirrored for of texture.
		3. GL_CLAMP: extend pixels to the edge.
		4. Apply a coloured border.

* Image loading:
	* Most commonly used library: SOIL(Simple OpenGL Image Library)

* Samplers:
	* Samplers are variables used by shader to access the texture.
	* Shaders access textures that are bind to a specific texture unit.
	* Steps involved in application:
		1. we need to generate a texture.
		2. Bind it to a texture unit.
		3. Specify the unit to the sampler variable in the shader.
