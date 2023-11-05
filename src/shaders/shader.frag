#version 460

in vec3 normal;
in vec3 fragPos;

uniform vec3 color;
uniform float ambient;
uniform vec3 lightPos;
uniform vec3 lightColor;

out vec4 fragColor;

void main()
{
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    fragColor = vec4((ambient + diffuse) * color, 1.0);
}