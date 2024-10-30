#version 330 core
out vec4 FragmentColor;

uniform vec3 LightColor;
uniform vec3 ObjectColor;

void main()
{
    FragmentColor = vec4(LightColor * ObjectColor, 1.0f);
}
