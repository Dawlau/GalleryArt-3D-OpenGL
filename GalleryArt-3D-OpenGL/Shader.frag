#version 400

in vec3 FragPos;
in vec3 Normal;
in vec3 inLightPos;
in vec3 inViewPos;

out vec4 out_Color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform int drawShadow;

void main() {

  if (drawShadow == 0){
    float ambientStrength = 0.5f;
    vec3 ambient_light = ambientStrength * lightColor;
    vec3 ambient_term = ambient_light * objectColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(inLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse_light = lightColor;
    vec3 diffuse_term = diff * diffuse_light * objectColor;

    float specularStrength = 5.0f;
    float shininess = 10.0f;
    vec3 viewDir = normalize(inViewPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular_light = specularStrength  * lightColor;
    vec3 specular_term = spec * specular_light * objectColor;

    vec3 result = (ambient_term + diffuse_term + specular_term);
    out_Color = vec4(result, 1.0f);
  }
  else {
    out_Color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
  }
}