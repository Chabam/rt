#version 460

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

uniform sampler2D inTexture;

uniform vec3 color;
uniform float specularStr;
uniform uint shininess;
uniform bool emitsLight;
uniform bool hasTexture;

uniform float ambientStr;
uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 cameraPos;

out vec4 fragColor;

void main()
{
    vec4 vertexColor = vec4(color, 1.0);
    if (emitsLight)
    {
        fragColor = vertexColor;
        return;
    }

    if (hasTexture)
    {
        vertexColor = texture(inTexture, texCoord);
    }

    vec3 ambient = ambientStr * lightColor;

    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * lightColor;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    vec3 specular = pow(max(dot(normal, halfwayDir), 0.0), shininess) * specularStr * lightColor;

    vec4 texColor = texture(inTexture, texCoord);

    fragColor = vec4(ambient + diffuse + specular, 1.0) * vertexColor;
}