#version 150

in vec3 vertexPosition;
in vec3 vertexNormal;
in vec4 vertexTangent;
in vec2 vertexTexCoord;
in vec3 pos;
in int isSelected;
in int faceId;

out vec3 worldPosition;
out vec3 worldNormal;
out vec4 worldTangent;
out vec2 texCoord;
flat out int selected;
flat out int face;

uniform mat4 modelMatrix;
uniform mat3 modelNormalMatrix;
uniform mat4 mvp;

void main()
{
    // Pass the texture coordinates through
    texCoord = vertexTexCoord;

    // Pass through instance data
    selected = isSelected;
    face = faceId;

    // Offset for instance position
    vec3 offsetPos = vertexPosition + pos;

    // Transform position, normal, and tangent to world space
    worldPosition = vec3(modelMatrix * vec4(offsetPos, 1.0));
    worldNormal = normalize(modelNormalMatrix * vertexNormal);
    worldTangent.xyz = normalize(vec3(modelMatrix * vec4(vertexTangent.xyz, 0.0)));
    worldTangent.w = vertexTangent.w;

    gl_Position = mvp * vec4(offsetPos, 1.0);
}
