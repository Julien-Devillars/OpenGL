This repository contains all the small openGL project that I made (which are inspired by the book superbible sixth edition).

The basic source code is taken from [Tomasz Gałaj](https://shot511.github.io/) with some modification made by myself to able multi projects.

# GL1_BasicPoint

A basic project to draw a single point or a single triangle with OpenGL.

## How to do this ?

  * **Include a window library**, we are using GLFW3 for our project but SDL2 can works too.
  * **Initialize the window**, depending of the library, the window can be initialize differently. Don't forget to add the background color of the window with **glClearColor** and the size of the **Viewport**
  * **Create your program** with **glCreateProgram**
  * **Add the different shaders**
    * shader_source code  
    * shader_type with GL_*SHADERNAME*_SHADER with *SHADERNAME* :
      * GL_VERTEX_SHADER
      * GL_FRAGMENT_SHADER
      * GL_GEOMETRY_SHADER
      * GL_TESS_CONTROL_SHADER
      * GL_TESS_EVALUATION_SHADER
    * Create your shader_object with **glCreateShader(shader_type)**
    * Link the shader_source code to your shader_object with **glShaderSource(shader_source, 1, shader_object, nullptr)**
    * Compile the shader with **glCompileShader(shader_object)**
    * Attach the shader to your program with **glAttachShader**
    * Once the shader attached to the program, you can delete it with **glDelete**
  * Don't forget to create a **V**ertex **A**rray **O**bject with **glGenVertexArrays(1 , &vao)** and to bind on it with **glBindVertexArray(vao)** when you want to use it.
  * Finally, link the program that you want with **glLinkProgram** then use it with **glUseProgram**
  * Now you can draw with the function **glDrawArrays** in the runloop which can display elements such as
    * points with **GL_POINTS**
    * triangles with **GL_TRIANGLES**
    * quads with **GL_QUADS**
    * patches with **GL_PATCHES**
  
The project use a vertex shader and a fragment shader.


# GL2_AllShaders

The second project present the different shader possibles which was introduce in the previous project under the term *SHADERNAME*, it follows the basic pipeline used by opengl.

![pipeline-detail](https://user-images.githubusercontent.com/45456710/94932518-7c94db80-04c9-11eb-89d0-dae84ef9f7fb.png)

## Vertex Shader
## Tesselation Control Shader
## Tesselation Evaluation Shader
## Geometry Shader
## Fragment Shader
