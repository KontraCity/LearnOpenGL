#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 LightPosition;

void main()
{
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    FragPos = vec3(View * Model * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(View * Model))) * aNormal;
    LightPos = vec3(View * vec4(LightPosition, 1.0f));
}
