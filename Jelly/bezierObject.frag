#version 330 core

out vec4 fragColor;
in vec3 v_Position;       // Interpolated position for this fragment.
in vec3 v_Normal;

struct Light
{
    vec4 position;
    vec3 intensity;
};

uniform Light light;
struct Material {
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    float shininess;
};
uniform Material material;

void main()
{
    vec3 n = normalize( v_Normal);
    vec3 s = normalize( light.position.xyz - v_Position);
    vec3 v = normalize( -v_Position.xyz);
    vec3 h = normalize( v + s);
    float sdn = dot( s, n);
    vec3 ambient = material.Ka;
    vec3 diffuse = material.Kd * max( sdn, 0.0);
    vec3 specular = material.Ks * mix( 0.0, pow( dot(h, n), material.shininess), step( 0.0, sdn));
    fragColor = vec4(light.intensity * (ambient + diffuse + specular), 1.0);
}







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