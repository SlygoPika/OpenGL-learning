# OpenGL-learning NOTES

Bullet notes:
  - Glad and GLEW are basically interchangeable (They are set up differently)
  - No real difference between OpenGL and regular data types. Try to use regular data types when practicing.

GLFW:
  - Used to display a window
  - Must be initialized at the beginning
  - Must be given hints (version, profile, forward compact [if macOS])
  - Must creat window (check if it failed) & make window the current context
  - Terminate glfw at the end of the program


VBO (Vertex Buffer Object):
  - Stores Vertex Array
  - Stores data to interpret vertex array
  * IMPORTANT METHODS:
    - glGenBuffers() : Generate Buffer
    - glBufferData() : Assign vertex array
    - glEnableVertexAttribArray() : Enable VBO (?)
    - glVertexAttribPointer() : Tell OpenGL how to interpret vertex array

## Shaders:
  * Shader can be written as: C++ strings, external files (.vert, .frag)
  * ### GLSL:
    - Data types:
      - vec4 : vector with 4 components
    - "#version 330 core" : Means we're using GLSL (OpenGL shading language) version 330. Core doesn't allow deprecated features.
    - Shader must have a main function [void main()]
    - "in" : Variable inputed into shader
    - "out" : Ouput variable
    - "layout(location = #)" : Location of variable. Set using glVertexAttribPointer().
    - gl_Position (vec4) : vertex position vector
    
  * ### IMPORTANT METHODS:
    + **Compiling Shaders:**
      - **glCreateProgram()** : Creates program object (object to which shader objects can be attached). Returns program ID (unsigned int).
      - **glCreateShader(SHADER_TYPE)** : Creates empty shader object. Returns shader ID (unsigned int).
        - SHADER_TYPE examples: GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
      - **glShaderSource(shader_id, num_of_elem, shader_string_ptr, length [null_ptr])** : Set up shader. Can be used to set up empty shader from glCreateShader().
      - **glCompileShader(shader_id)** : Compiles shader.
      - **glAttachShader(program_id, shader_id)** : Attaches shader to program.
      - **glLinkProgram(program_id)** : Links program. Attached shaders will be used to create an executable that will run on the programmable vertex shader.
      - **glValidateProgram(program_id)** : Checks to see whether the executables contained in program can execute given the current OpenGL state.
      - **glDeleteShader(shader_id)** : Delete shader. Do this after attaching shader.
      - **glDeleteProgram(shader_id)** : Delete shader. Do this at end.
    + **Error Handling:**
      - **glGetShaderiv(shader_id, PROPERTY_NAME, result_ptr)** : Gets shader property requested and outputs it onto result_ptr
      - **glGetInfoLog([...])**
      
    
