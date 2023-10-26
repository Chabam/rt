#version 400

in vec3 inPos;

uniform vec4 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 outColor;

void main()
{
    gl_Position = model * view * projection * vec4(inPos, 1.0);
    outColor = color; // set ourColor to the input color we got from the vertex data
}