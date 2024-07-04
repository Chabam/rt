#version 460

in vec3 normal;
in vec2 texCoord;
in vec3 tangentLightPos;
in vec3 tangentCameraPos;
in vec3 tangentFragPos;

uniform sampler2D inTexture;
uniform sampler2D inNormalMap;

uniform vec3 color;
uniform float specularStr;
uniform uint shininess;
uniform bool emitsLight;
uniform bool hasTexture;
uniform bool hasNormalMap;

uniform float ambientStr;
uniform vec3 lightColor;

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

    vec3 outNormal = normal;
    if (hasNormalMap)
    {
        outNormal = texture(inNormalMap, texCoord).rgb;
        outNormal = normalize(outNormal * 2.0 - 1.0);
    }

    vec3 ambient = ambientStr * lightColor;

    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
    vec3 diffuse = max(dot(outNormal, lightDir), 0.0) * lightColor;

    vec3 viewDir = normalize(tangentCameraPos - tangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    vec3 specular = pow(max(dot(outNormal, halfwayDir), 0.0), shininess) * specularStr * lightColor;

    vec4 texColor = texture(inTexture, texCoord);

    fragColor = vec4(ambient + diffuse + specular, 1.0) * vertexColor;
}