#version 330 core

out vec4 FragColor;

in vec3 vFragPos;
in vec3 vNormal;
in vec3 vLightPos;   // extra in variable, since we need the light position in view space we calculate this in the vertex shader

uniform vec3 lightColor;
uniform vec3 objectColor;


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
    vec3 viewDir = normalize(-vFragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 
    
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}









//out vec4 fragColor;
//in vec3 v_Position;       // Interpolated position for this fragment.
//in vec3 v_Normal;

//struct Light
//{
//    vec4 position;
//    vec3 intensity;
//};

//uniform Light light;
//struct Material {
//    vec3 Ka;
//    vec3 Kd;
//    vec3 Ks;
//    float shininess;
//};
//uniform Material material;

//void main()
//{
//    vec3 n = normalize( v_Normal);
//    vec3 s = normalize( light.position.xyz - v_Position);
//    vec3 v = normalize( -v_Position.xyz);
//    vec3 h = normalize( v + s);
//    float sdn = dot( s, n);
//    vec3 ambient = material.Ka;
//    vec3 diffuse = material.Kd * max( sdn, 0.0);
//    vec3 specular = material.Ks * mix( 0.0, pow( dot(h, n), material.shininess), step( 0.0, sdn));
//    fragColor = vec4(light.intensity * (ambient + diffuse + specular), 1.0);
//}







//in vec3 v_Position;       // Interpolated position for this fragment.
//in vec4 v_Color;          // This is the color from the vertex shader interpolated across the
//in vec3 v_Normal;

//uniform vec3 u_LightPos;
//out vec4 fColor;

//void main()
//{	
//	 float distance = length(u_LightPos - v_Position);
//    vec3 lightVector = normalize(u_LightPos - v_Position);
 
//    float diffuse = max(dot(v_Normal, lightVector), 0.1);
 
//    diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));
 
//    //gl_FragColor = v_Color * diffuse;
//	fColor = v_Color * diffuse;
//}