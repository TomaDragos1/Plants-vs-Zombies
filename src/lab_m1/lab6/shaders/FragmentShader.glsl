#version 330

// Input
// TODO(student): Get values from vertex shader

// Output
// Atribute de intrare de la Vertex Shader
in vec3 frag_color;

// Variabila de output către framebuffer
out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(frag_color, 1.0);

}