#version 330 core

struct LightAttenuation
{
    float constant;
    float linear;
    float quadratic;
};

struct LightProperties
{
    float innerCutoff;
    float outerCutoff;
    float ambient;
    float diffuse;
    float specular;
    LightAttenuation attenuation;
};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

out vec4 FragColor;
in vec3 FragPos;
in vec4 FragScreenPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 LightPosition;
in vec3 LightDirection;

uniform vec3 uObjectColor;
uniform Material uMaterial;
uniform vec3 uLightColor;
uniform LightProperties uLightProperties;

float CalcAttenuation()
{
    float distanceToFrag = length(LightPosition - FragPos);
    float linear = uLightProperties.attenuation.linear * distanceToFrag;
    float quadratic = uLightProperties.attenuation.quadratic * (distanceToFrag * distanceToFrag);
    return 1.0f / (uLightProperties.attenuation.constant + linear + quadratic);
}

float CalcSpotlight(vec3 lightTarget)
{
    float theta = dot(lightTarget, normalize(-LightDirection));
    return smoothstep(uLightProperties.outerCutoff, uLightProperties.innerCutoff, theta);
}

vec3 CalcAmbient()
{
    return uLightColor * uLightProperties.ambient * vec3(texture(uMaterial.diffuse, TexCoords));;
}

vec3 CalcDiffuse(vec3 lightTarget, vec3 normal)
{
    float diffuseValue = max(0.0f, dot(lightTarget, normal));
    return uLightColor * uLightProperties.diffuse * diffuseValue * vec3(texture(uMaterial.diffuse, TexCoords));
}

vec3 CalcSpecular(vec3 lightTarget, vec3 normal)
{
    vec3 viewDirection = normalize(-FragPos);
    vec3 reflectDirection = reflect(-lightTarget, normal);
    float specularValue = pow(max(0.0f, dot(viewDirection, reflectDirection)), uMaterial.shininess);
    return uLightColor * uLightProperties.specular * specularValue * vec3(texture(uMaterial.specular, TexCoords));
}

void main()
{
    // Multipliers
    vec3 lightTarget = normalize(LightPosition - FragPos);
    float attenuation = CalcAttenuation();
    float spotlight = CalcSpotlight(lightTarget);

    // Lighting
    vec3 normal = normalize(Normal);
    vec3 ambient = CalcAmbient();
    vec3 diffuse = CalcDiffuse(lightTarget, normal);
    vec3 specular = CalcSpecular(lightTarget, normal);

    FragColor = vec4(attenuation * spotlight * (ambient + diffuse + specular) * uObjectColor, 1.0f);
}
