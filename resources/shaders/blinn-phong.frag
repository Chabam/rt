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
    if (emitsLight)
    {
        fragColor = vec4(color, 1.0);
        return;
    }

    vec3 ambient = ambientStr * lightColor;

    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * lightColor;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    vec3 specular = pow(max(dot(normal, halfwayDir), 0.0), shininess) * specularStr * lightColor;

    vec4 texColor = texture(inTexture, texCoord);
    vec4 vertex_color = vec4((ambient + diffuse + specular) * color, 1.0);

    fragColor = vertex_color;
    if (hasTexture)
    {
        fragColor = mix(texColor, vertex_color, 0.2);
    }
}