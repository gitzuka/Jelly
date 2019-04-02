#version 330 core

out vec4 FragColor;
in vec3 vFragPos;
in vec3 vNormal;
in vec3 vLightPos;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 eyePos;
uniform float materialShininess;
uniform float materialKd;
uniform float materialKs;


void main()
{
    // ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;    
    
     // diffuse 
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(vLightPos - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(eyePos -vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}