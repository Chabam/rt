#version 460

in vec3 normal;
in vec3 fragPos;

uniform vec3 color;
uniform float specularStr;

uniform float ambient;
uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 cameraPos;

out vec4 fragColor;

void main()
{
    vec3 lightDir = normalize(lightPos - fragPos);

    vec3 diffuse = max(dot(normal, lightDir), 0.0) * lightColor;
    
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    vec3 specular = pow(max(dot(viewDir, reflectionDir), 0.0), 32) * specularStr * lightColor;
    
    fragColor = vec4((ambient + diffuse + specular) * color, 1.0);
}