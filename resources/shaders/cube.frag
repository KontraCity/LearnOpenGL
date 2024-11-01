#version 330 core

struct LightProperties
{
    float ambient;
    float diffuse;
    float specular;
};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 LightPosition;

uniform vec3 uObjectColor;
uniform Material uMaterial;
uniform vec3 uLightColor;
uniform LightProperties uLightProperties;

void main()
{
    // Ambient lighting
    vec3 ambient = uLightColor * uLightProperties.ambient * vec3(texture(uMaterial.diffuse, TexCoords));

    // Diffuse lighting
    vec3 lightDirection = normalize(LightPosition - FragPos);
    vec3 normal = normalize(Normal);
    float diffuseValue = max(0.0f, dot(lightDirection, normal));
    vec3 diffuse = uLightColor * uLightProperties.diffuse * diffuseValue * vec3(texture(uMaterial.diffuse, TexCoords));

    // Specular lighting
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularValue = pow(max(0.0f, dot(viewDirection, reflectDirection)), uMaterial.shininess);
    vec3 specular = uLightColor * uLightProperties.specular * specularValue * vec3(texture(uMaterial.specular, TexCoords));

    vec3 result = (ambient + diffuse + specular) * uObjectColor;
    FragColor = vec4(result, 1.0f);
}
