#version 330

// Input
// TODO(student): Get vertex attributes from each location

// Atribute de intrare
layout(location = 0) in vec3 v_position;
layout(location = 2) in vec3 v_color;
layout(location = 1) in vec3 v_normal;
layout(location = 3) in vec2 v_texCoord;

// Atribute de ieșire către Fragment Shader
out vec3 frag_color;
out vec3 frag_normal;
out vec2 frag_texCoord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
// TODO(student): Output values to fragment shader
uniform vec3 Color;
uniform float Poz;

void main()
{
// TODO(student): Send output to fragment shader
    frag_color = v_normal * Color;
    //frag_normal = v_normal;
    // frag_texCoord = v_texCoord;
    vec3 pozition = v_position * sin(Poz);
    gl_Position = Projection * View * Model * vec4(pozition, 1.0);

}