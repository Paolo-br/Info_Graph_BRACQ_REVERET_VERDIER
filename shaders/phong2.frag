#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D diffuse_map;

uniform vec3 ambientColor;
uniform vec3 specularColor;

void main()
{
    // Couleur diffuse (texture)
    vec3 diffuseColor = texture(diffuse_map, TexCoord).rgb;

    // Calcul de l'ombrage
    vec3 ambient = 0.1 * diffuseColor;  // lumière ambiante

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;

    // Calcul de la lumière spéculaire
    vec3 viewDir = normalize(- FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * specularColor;

    // Combinaison de la lumière
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
