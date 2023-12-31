#version 460

in vec3 inPos;
in vec3 inNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

out vec3 normal;
out vec3 fragPos;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0);
    fragPos = vec3(model * vec4(inPos, 1.0));
    normal = normalMatrix * inNorm;
}