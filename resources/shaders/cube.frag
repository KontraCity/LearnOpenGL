#version 330 core

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
in DirectionalLight ioDirectionalLight;
in PointLight ioPointLight;
in SpotLight ioSpotLight;

uniform vec3 uObjectColor;
uniform Material uMaterial;

vec3 CalcDirectionalLight(DirectionalLight light)
{
    // Ambient lighting
    vec3 ambient = light.color * light.properties.ambient * vec3(texture(uMaterial.diffuse, TexCoords));

    // Diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(-light.direction);
    float diffuseValue = max(0.0f, dot(normal, lightDirection));
    vec3 diffuse = light.color * light.properties.diffuse * diffuseValue * vec3(texture(uMaterial.diffuse, TexCoords));

    // Specular lighting
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularValue = pow(max(0.0f, dot(viewDirection, reflectDirection)), uMaterial.shininess);
    vec3 specular = light.color * light.properties.specular * specularValue * vec3(texture(uMaterial.specular, TexCoords));
    
    vec3 result = ambient + diffuse + specular;
    return result;
}

vec3 CalcPointLight(PointLight light)
{
    // Ambient lighting
    vec3 ambient = light.color * light.properties.ambient * texture(uMaterial.diffuse, TexCoords).rgb;

    // Diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diffuseValue = max(0.0f, dot(lightDirection, normal));
    vec3 diffuse = light.color * light.properties.diffuse * diffuseValue * texture(uMaterial.diffuse, TexCoords).rgb;

    // Specular lighting
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularValue = pow(max(0.0f, dot(viewDirection, reflectDirection)), uMaterial.shininess);
    vec3 specular = light.color * light.properties.specular * specularValue * texture(uMaterial.specular, TexCoords).rgb;
    
    // Attenuation
    float distanceToFrag = length(light.position - FragPos);
    float linear = light.attenuation.linear * distanceToFrag;
    float quadratic = light.attenuation.quadratic * (distanceToFrag * distanceToFrag);
    float attenuation = 1.0f / (light.attenuation.constant + linear + quadratic);

    vec3 result = ambient + diffuse + specular;
    return result * attenuation;
}

vec3 CalcSpotLight(SpotLight light)
{
    // Ambient lighting
    vec3 ambient = light.color * light.properties.ambient * vec3(texture(uMaterial.diffuse, TexCoords));

    // Diffuse lighting
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);
    float diffuseValue = max(0.0f, dot(normal, lightDirection));
    vec3 diffuse = light.color * light.properties.diffuse * diffuseValue * vec3(texture(uMaterial.diffuse, TexCoords));

    // Specular lighting
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularValue = pow(max(0.0f, dot(viewDirection, reflectDirection)), uMaterial.shininess);
    vec3 specular = light.color * light.properties.specular * specularValue * vec3(texture(uMaterial.specular, TexCoords));
    
    // Spot lighting
    float theta = dot(lightDirection, normalize(-light.direction));
    float spotlight = smoothstep(light.cutoff.outer, light.cutoff.inner, theta);

    // Attenuation
    float distanceToFrag = length(light.position - FragPos);
    float linear = light.attenuation.linear * distanceToFrag;
    float quadratic = light.attenuation.quadratic * (distanceToFrag * distanceToFrag);
    float attenuation = 1.0f / (light.attenuation.constant + linear + quadratic);

    vec3 result = ambient + (diffuse + specular) * spotlight;
    return result * attenuation;
}

void main()
{
    vec3 directionalLight = CalcDirectionalLight(ioDirectionalLight);
    vec3 pointLight = CalcPointLight(ioPointLight);
    vec3 spotLight = CalcSpotLight(ioSpotLight);
    FragColor = vec4(directionalLight + pointLight + spotLight, 1.0f);
}
