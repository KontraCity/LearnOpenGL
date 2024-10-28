#version 330 core
out vec4 FragmentColor;
in vec2 TextureCoordinates;

uniform sampler2D ContainerTexture;
uniform sampler2D AwesomeFaceTexture;
uniform float TextureMix;

void main()
{
    FragmentColor = mix(
        texture(ContainerTexture, TextureCoordinates),
        texture(AwesomeFaceTexture, TextureCoordinates),
        texture(AwesomeFaceTexture, TextureCoordinates).a * TextureMix
    );
}
