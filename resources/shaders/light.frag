#version 330 core
out vec4 FragmentColor;

uniform vec3 uLightColor;

void main()
{
    FragmentColor = vec4(uLightColor, 1.0f);
}
