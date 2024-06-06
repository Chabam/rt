#version 460

in vec3 inPos;
in vec3 inNorm;
in vec2 inTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0);
    fragPos = vec3(model * vec4(inPos, 1.0));
    normal = normalize(normalMatrix * inNorm);
    texCoord = inTexCoord;
}