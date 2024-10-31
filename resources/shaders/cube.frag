#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;

uniform vec3 LightColor;
uniform vec3 ObjectColor;

void main()
{
    // Ambient lighting
    const float AmbientStrength = 0.1f;
    vec3 ambient = LightColor * AmbientStrength;

    // Diffuse lighting
    vec3 lightDirection = normalize(LightPos - FragPos);
    vec3 normal = normalize(Normal);
    vec3 diffuse = LightColor * max(0.0f, dot(lightDirection, normal));

    // Specular lighting
    const float SpecularStrength = 0.5f;
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    vec3 specular = LightColor * SpecularStrength * pow(max(0.0f, dot(viewDirection, reflectDirection)), 32);

    vec3 result = (ambient + diffuse + specular) * ObjectColor;
    FragColor = vec4(result, 1.0f);
}
