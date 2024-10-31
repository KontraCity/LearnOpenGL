#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

out vec4 FragColor;
in vec3 FragPos;
in vec3 Normal;
in vec3 LightPosition;

uniform vec3 uObjectColor;
uniform Material uMaterial;
uniform vec3 uLightColor;
uniform vec3 uLightProperties;

void main()
{
    // Ambient lighting
    vec3 ambient = uLightColor * uLightProperties.x * uMaterial.ambient;

    // Diffuse lighting
    vec3 lightDirection = normalize(LightPosition - FragPos);
    vec3 normal = normalize(Normal);
    float diffuseValue = max(0.0f, dot(lightDirection, normal));
    vec3 diffuse = uLightColor * uLightProperties.y * uMaterial.diffuse * diffuseValue;

    // Specular lighting
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularValue = pow(max(0.0f, dot(viewDirection, reflectDirection)), uMaterial.shininess * 128.0);
    vec3 specular = uLightColor * uLightProperties.z * uMaterial.specular * specularValue;

    vec3 result = (ambient + diffuse + specular) * uObjectColor;
    FragColor = vec4(result, 1.0f);
}
