#version 460

in vec3 inPos;
in vec3 inNorm;
in vec2 inTexCoord;
in vec3 inTangent;
in vec3 inBiTangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform bool hasNormalMap;

out vec3 normal;
out vec2 texCoord;
out vec3 tangentLightPos;
out vec3 tangentCameraPos;
out vec3 tangentFragPos;

void main()
{
    gl_Position = projection * view * model * vec4(inPos, 1.0);
    normal = normalize(normalMatrix * inNorm);
    texCoord = inTexCoord;

    // TODO: temporary hack to have UVs working properly on models!
    if (!hasNormalMap)
    {
        tangentLightPos = lightPos;
        tangentCameraPos = cameraPos;
        tangentFragPos = vec3(model * vec4(inPos, 1.0));
        return;
    }

    vec3 T = normalize(vec3(model * vec4(inTangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(inBiTangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(inNorm, 0.0)));

    mat3 TBN = transpose(mat3(T, B, N));

    tangentLightPos = TBN * lightPos;
    tangentCameraPos = TBN * cameraPos;
    tangentFragPos = TBN * vec3(model * vec4(inPos, 1.0));
}