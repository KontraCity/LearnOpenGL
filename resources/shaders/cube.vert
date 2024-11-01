#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 LightPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uLightPosition;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    FragPos = vec3(uView * uModel * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(uView * uModel))) * aNormal;
    TexCoords = aTexCoords;
    LightPosition = vec3(uView * vec4(uLightPosition, 1.0f));
}
