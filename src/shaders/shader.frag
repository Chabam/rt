#version 400

out vec4 FragColor;
in vec4 outColor;

void main()
{
    FragColor = outColor;
}