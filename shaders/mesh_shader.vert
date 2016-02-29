attribute vec4 vertex_position;  // the vertex position (in the local space) from VBO
attribute vec4 vertex_color;	 // the vertex color from VBO
attribute vec4 vertex_normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec4 fragment_color;	 // The color output into the fragment shader
varying vec4 fragment_normal;

void main()
{
    float a = vertex_color[0];
    fragment_color = vertex_color;//vec4(a,a,a,a)
// Using the built-in OpenGL modelview_projection function,
// we can convert the vertex from the local space to the clip space.
// Note that a better way as required by more recent OpenGL versions, 
// is to define the matrix as uniform variables manually.

// The user can achieve camera motion by changing gl_ModelViewProjectionMatrix
// using OpenGL transformation functions
   
   mat4 scale = mat4(1 ,0    ,0    ,0,
                     0   ,1  ,0    ,0,//-0.25,
                     0   ,0    ,1  ,0,
                     0   ,0    ,0    ,1);
   mat4 temp = gl_ModelViewProjectionMatrix * scale;
  
	//gl_Position = temp * vertex_position;
	gl_Position = projection * view * model * vertex_position *temp;
    
}