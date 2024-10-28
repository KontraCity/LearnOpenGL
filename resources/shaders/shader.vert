#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoordinates;
out vec2 TextureCoordinates;
uniform mat4 Transform;

void main()
{
    gl_Position = Transform * vec4(aPos, 1.0);
    TextureCoordinates = aTextureCoordinates;
}
