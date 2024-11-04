#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

struct LightAttenuation
{
    float constant;
    float linear;
    float quadratic;
};

struct LightCutoff
{
    float inner;
    float outer;
};

struct LightProperties
{
    float ambient;
    float diffuse;
    float specular;
};

struct DirectionalLight
{
    vec3 color;
    LightProperties properties;
    vec3 direction;
};

struct PointLight
{
    vec3 color;
    LightAttenuation attenuation;
    LightProperties properties;
    vec3 position;
};

struct SpotLight
{
    vec3 color;
    LightAttenuation attenuation;
    LightCutoff cutoff;
    LightProperties properties;
    vec3 position;
    vec3 direction;
};

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out DirectionalLight ioDirectionalLight;
out PointLight ioPointLight;
out SpotLight ioSpotLight;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform DirectionalLight uDirectionalLight;
uniform PointLight uPointLight;
uniform SpotLight uSpotLight;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    FragPos = vec3(uView * uModel * vec4(aPos, 1.0f));
    Normal = mat3(transpose(inverse(uView * uModel))) * aNormal;
    TexCoords = aTexCoords;
    
    ioDirectionalLight = uDirectionalLight;
    ioDirectionalLight.direction = vec3(uView * vec4(ioDirectionalLight.direction, 0.0f));

    ioPointLight = uPointLight;
    ioPointLight.position = vec3(uView * vec4(ioPointLight.position, 1.0f));

    ioSpotLight = uSpotLight;
    ioSpotLight.position = vec3(uView * vec4(ioSpotLight.position, 1.0f));
    ioSpotLight.direction = vec3(uView * vec4(ioSpotLight.direction, 0.0f));
}
